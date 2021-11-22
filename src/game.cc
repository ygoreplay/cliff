#include "common.hpp"
#include "game.hpp"

Game::Game(BufferReader* data) :
    data(data), duelId(0) { }
Game::~Game() = default;

Game* Game::createDuel(const Replay::Header &header, BufferReader* data) {
    Game* result = new Game(data);
    std::memcpy(&result->header, &header, sizeof(Replay::Header));
    if (!result->initialize()) {
        delete result;
        return nullptr;
    }

    return result;
}

bool Game::initialize() {
    this->information.isFirst = true;
    this->information.isTag = !!(this->header.flag & REPLAY_TAG);
    this->information.isSingleMode = !!(this->header.flag & REPLAY_SINGLE_MODE);
    this->information.tag_player[0] = false;
    this->information.tag_player[1] = false;
    this->information.isStarted = true;
    this->information.isFinished = true;
    this->information.isReplay = true;
    this->information.isReplaySkiping = false;

    mt19937 random;
    random.reset(this->header.seed);

    if (this->information.isTag) {
        this->data->readName(this->information.hostname);
        this->data->readName(this->information.hostname_tag);
        this->data->readName(this->information.clientname);
        this->data->readName(this->information.clientname_tag);
    } else {
        this->data->readName(this->information.hostname);
        this->data->readName(this->information.clientname);
    }

    this->duelId = create_duel(random.rand());
    auto start_lp = this->data->read<int32_t>();
    auto start_hand = this->data->read<int32_t>();
    auto draw_count = this->data->read<int32_t>();
    auto opt = this->data->read<int32_t>();
    int32_t duel_rule = opt >> 16;

    this->information.duel_rule = duel_rule;

    set_player_info(this->duelId, 0, start_lp, start_hand, draw_count);
    set_player_info(this->duelId, 1, start_lp, start_hand, draw_count);

    this->information.lp[0] = start_lp;
    this->information.lp[1] = start_lp;
    this->information.turn = 0;

    auto readDecks = [this](int owner, int playerId) {
        auto mainDeckCount = this->data->read<int32_t>();
        for (int32_t i = 0; i < mainDeckCount; ++i) {
            new_card(this->duelId, this->data->read<int32_t>(), owner, playerId, LOCATION_DECK, 0, POS_FACEDOWN_DEFENSE);
        }

        auto extraDeckCount = this->data->read<int32_t>();
        for (int32_t i = 0; i < extraDeckCount; ++i) {
            new_card(this->duelId, this->data->read<int32_t>(), owner, playerId, LOCATION_EXTRA, 0, POS_FACEDOWN_DEFENSE);
        }
    };

    auto readTagDecks = [this](uint8_t owner) {
        auto mainDeckCount = this->data->read<int32_t>();
        for(int i = 0; i < mainDeckCount; ++i)
            new_tag_card(this->duelId, this->data->read<int32_t>(), owner, LOCATION_DECK);

        auto extraDeckCount = this->data->read<int32_t>();
        for(int i = 0; i < extraDeckCount; ++i)
            new_tag_card(this->duelId, this->data->read<int32_t>(), owner, LOCATION_EXTRA);
    };

    if(!this->information.isSingleMode) {
        if(!(opt & DUEL_TAG_MODE)) {
            readDecks(0, 0);
            if (opt & DUEL_TAG_MODE) {
                readTagDecks(0);
            }

            readDecks(1, 1);
            if (opt & DUEL_TAG_MODE) {
                readTagDecks(1);
            }
        }
    } else {
        char filename[256];
        size_t slen = this->data->read<int16_t>();
        this->data->readBytes((byte*)filename, slen);
        filename[slen] = 0;

        if(!preload_script(this->duelId, filename, 0)) {
            return false;
        }
    }

    start_duel(this->duelId, opt);
    return true;
}

int Game::process() {
    return ::process(this->duelId);
}
void Game::getMessage(byte* buffer) const {
    get_message(this->duelId, buffer);
}
void Game::setResponse(byte* response) {
    set_responseb(this->duelId, response);
}
