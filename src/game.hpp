#ifndef CLIFF_GAME_HPP
#define CLIFF_GAME_HPP

class Game {
private:
    struct Information {
        bool isStarted;
        bool isFinished;
        bool isReplay;
        bool isReplaySkiping;
        bool isFirst;
        bool isTag;
        bool isSingleMode;
        bool is_shuffling;
        bool tag_player[2];
        int lp[2];
        int duel_rule;
        int turn;
        short curMsg;
        wchar_t hostname[20];
        wchar_t clientname[20];
        wchar_t hostname_tag[20];
        wchar_t clientname_tag[20];
        wchar_t strLP[2][16];
        wchar_t* vic_string;
        unsigned char player_type;
        unsigned char time_player;
        unsigned short time_limit;
        unsigned short time_left[2];
        bool isReplaySwapped;
    };

public:
    static Game* createDuel(const Replay::Header& header, BufferReader* data);

private:
    Game() = delete;
    explicit Game(BufferReader* data);
    ~Game();

public:
    int process();
    void getMessage(byte* buffer) const;
    void setResponse(byte* response);

public:
    [[nodiscard]] const Game::Information& getInformation() const {
        return this->information;
    }

private:
    bool initialize();

private:
    intptr_t duelId;
    BufferReader* data;
    Game::Information information{};
    Replay::Header header{};
};

#endif // CLIFF_GAME_HPP
