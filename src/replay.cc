#include "common.hpp"

byte Replay::scriptBuffer[0x20000];
std::unordered_map<size_t, Replay*>* Replay::instances = nullptr;
std::string Replay::scriptDirectory = "./";

Replay* Replay::fromFile(const fs::path &path) {
    if (!fs::exists(path) || !fs::is_regular_file(path)) {
        return nullptr;
    }

    std::vector<uint8_t> fileData = FileUtils::readFile(path);
    auto* replay = new Replay(fileData);
    if (!replay->initialize()) {
        replay->release();
        return nullptr;
    }

    if (!Replay::instances) {
        Replay::instances = new std::unordered_map<size_t, Replay*>();
    }

    Replay::instances->insert({(size_t) replay, replay});
    return replay;
}

void Replay::setScriptDirectory(const std::string& directory) {
    Replay::scriptDirectory = directory;
}

Replay::Replay(std::vector<uint8_t> data)
        : compressedData(nullptr), data(nullptr) {
    this->compressedData = new BufferReader(data.data(), data.size());
}

Replay::~Replay() = default;

void Replay::release() {
    delete this;
}

bool Replay::initialize() {
    this->compressedData->read(this->header);

    byte replayData[0x20000];
    size_t replaySize = -1;
    if (this->header.flag & REPLAY_COMPRESSED) {
        byte compressedData[0x2000];
        size_t compressedSize = this->compressedData->readBytes(compressedData, 0x1000);
        replaySize = this->header.datasize;

        if (LzmaUncompress(replayData, &replaySize, compressedData, &compressedSize, this->header.props, 5) != SZ_OK)
            return false;
    } else {
        replaySize = this->compressedData->readBytes(replayData, 0x20000);
    }

    if (replaySize <= 0) {
        return false;
    }

    this->data = new BufferReader(replayData, replaySize);
    return true;
}

ParseResult* Replay::parse() {
    set_script_reader(Replay::readScript);
    set_card_reader(Replay::readCard);
    set_message_handler(Replay::handleMessage);

    this->duel = Game::createDuel(this->header, this->data);
    if (!this->duel) {
        return nullptr;
    }

    auto* parseResult = new ParseResult();
    char engineBuffer[0x1000];
    bool isContinuing = true;
    const auto& information = this->duel->getInformation();
    while (isContinuing) {
        auto result = this->duel->process();
        auto length = result & 0xFFFF;
        if (length > 0) {
            this->duel->getMessage(reinterpret_cast<byte*>(engineBuffer));
            isContinuing = this->analyzeMessage(engineBuffer, length, parseResult);
        }
    }

    return parseResult;
}

byte* Replay::readScript(const char* scriptName, int* length) {
    fs::path path = (scriptName + 2);
    fs::path expansionPath = "expansions/" / path;
    auto scriptReader = [](const fs::path& targetPath, byte* destBuffer, int* length) {
        std::ifstream file(Replay::scriptDirectory / targetPath);
        if (file.fail()) {
            return false;
        }

        size_t fileSize = FileUtils::getFileSize(file);
        if (fileSize > sizeof(scriptBuffer)) {
            file.close();
            return false;
        }

        file.read((char*)destBuffer, fileSize);
        file.close();
        *length = (int)fileSize;

        return true;
    };

    if (scriptReader(path, Replay::scriptBuffer, length) || scriptReader(expansionPath, Replay::scriptBuffer, length)) {
        return Replay::scriptBuffer;
    }

    return nullptr;
}

uint32_t Replay::readCard(uint32_t id, card_data* data) {
    if (!CardManager::getInstance()->get(id, reinterpret_cast<CardData*>(data)))
        memset(data, 0, sizeof(CardData));

    return 0;
}

uint32_t Replay::handleMessage(void* duel, uint32_t type) {
    return 0;
}

