#ifndef CLIFF_REPLAY_HPP
#define CLIFF_REPLAY_HPP

#define REPLAY_COMPRESSED	0x1
#define REPLAY_TAG			0x2
#define REPLAY_DECODED		0x4
#define REPLAY_SINGLE_MODE	0x8

class Game;

class Replay {
public:
    struct Header {
        unsigned int id;
        unsigned int version;
        unsigned int flag;
        unsigned int seed;
        unsigned int datasize;
        unsigned int hash;
        unsigned char props[8];
    };

private:
    static std::unordered_map<size_t, Replay*>* instances;
    static byte scriptBuffer[0x20000];
    static std::string scriptDirectory;

private:
    static byte* readScript(const char* scriptName, int* length);
    static uint32_t readCard(uint32_t id, card_data* data);
    static uint32_t handleMessage(void* duel, uint32_t type);

public:
    static Replay* fromFile(const fs::path& path);
    static void setScriptDirectory(const std::string& direcotry);

public:
    Replay() = delete;

private:
    explicit Replay(std::vector<uint8_t> data);
    ~Replay();

public:
    ParseResult* parse();
    void release();

private:
    bool initialize();
    bool analyzeMessage(char* message, size_t length, ParseResult* parseResult);
    bool readResponse();

private:
    BufferReader* compressedData;
    BufferReader* data;
    Replay::Header header;
    Game* duel;
};

#endif // CLIFF_REPLAY_HPP
