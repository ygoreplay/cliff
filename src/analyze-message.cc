#include "common.hpp"

bool Replay::readResponse() {
    byte response[64];
    if(this->data->position() >= this->data->size())
        return false;

    auto length = this->data->read<uint8_t>();
    if(length > 64)
        return false;

    this->data->readBytes(response, length);
    this->duel->setResponse(response);
    return true;
}

bool Replay::analyzeMessage(char* message, size_t length, ParseResult* parseResult) {
    int8_t player, count;
    byte* temp;
    BufferReader reader(reinterpret_cast<byte *>(message), length);

    while (reader.position() < length) {
        auto messageType = reader.read<uint8_t>();
        switch (messageType) {
            case MSG_RETRY: {
                return false;
            }
            case MSG_HINT: {
                reader.moveCursorForward(6);
                break;
            }

            case MSG_WIN: {
                reader.moveCursorForward(2);
                return false;
            }

            case MSG_SELECT_BATTLECMD: {
                player = reader.read<int8_t>();
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 11);
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 8 + 2);
                return this->readResponse();
            }

            case MSG_SELECT_IDLECMD: {
                player = reader.read<int8_t>();
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 7);
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 7);
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 7);
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 7);
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 7);
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 11 + 3);
                return this->readResponse();
            }

            case MSG_SELECT_EFFECTYN: {
                player = reader.read<int8_t>();
                reader.moveCursorForward(12);
                return this->readResponse();
            }

            case MSG_SELECT_YESNO: {
                player = reader.read<int8_t>();
                reader.moveCursorForward(4);
                return this->readResponse();
            }

            case MSG_SELECT_OPTION: {
                player = reader.read<int8_t>();
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 4);
                return this->readResponse();
            }

            case MSG_SELECT_CARD:
            case MSG_SELECT_TRIBUTE: {
                player = reader.read<int8_t>();
                reader.moveCursorForward(3);
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 8);
                return this->readResponse();
            }

            case MSG_SELECT_UNSELECT_CARD: {
                player = reader.read<int8_t>();
                reader.moveCursorForward(4);
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 8);
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 8);
                return this->readResponse();
            }

            case MSG_SELECT_CHAIN: {
                player = reader.read<int8_t>();
                count = reader.read<int8_t>();
                reader.moveCursorForward(10 + count * 13);
                return this->readResponse();
            }

            case MSG_SELECT_PLACE:
            case MSG_SELECT_DISFIELD:
            case MSG_SELECT_POSITION: {
                player = reader.read<int8_t>();
                reader.moveCursorForward(5);
                return this->readResponse();
            }

            case MSG_SELECT_COUNTER: {
                player = reader.read<int8_t>();
                reader.moveCursorForward(4);
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 9);
                return this->readResponse();
            }

            case MSG_SELECT_SUM: {
                reader.moveCursorForward();
                player = reader.read<int8_t>();
                reader.moveCursorForward(6);
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 11);
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 11);
                return this->readResponse();
            }

            case MSG_SORT_CARD: {
                player = reader.read<int8_t>();
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 7);
                return this->readResponse();
            }

            case MSG_CONFIRM_DECKTOP:
            case MSG_CONFIRM_EXTRATOP:
            case MSG_CONFIRM_CARDS: {
                player = reader.read<int8_t>();
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 7);
                break;
            }

            case MSG_SHUFFLE_DECK: {
                player = reader.read<int8_t>();
                break;
            }

            case MSG_SHUFFLE_HAND: {
                /*int oplayer = */reader.read<int8_t>();
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 4);
                break;
            }

            case MSG_SHUFFLE_EXTRA: {
                /*int oplayer = */reader.read<int8_t>();
                int count = reader.read<int8_t>();
                reader.moveCursorForward(count * 4);
                break;
            }

            case MSG_SWAP_GRAVE_DECK: {
                player = reader.read<int8_t>();
                break;
            }

            case MSG_REVERSE_DECK: {
                break;
            }

            case MSG_DECK_TOP: {
                reader.moveCursorForward(6);
                break;
            }

            case MSG_SHUFFLE_SET_CARD: {
                reader.moveCursorForward();
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 8);
                break;
            }

            case MSG_NEW_TURN: {
                player = reader.read<int8_t>();
                break;
            }

            case MSG_NEW_PHASE: {
                reader.moveCursorForward(2);
                break;
            }

            case MSG_MOVE: {
                temp = reader.current();
                auto cardId = reader.read<uint32_t>();
                uint8_t pc = temp[4];
                uint8_t pl = temp[5];
                uint8_t ps = temp[6];
                uint8_t pp = temp[7];
                uint8_t cc = temp[8];
                uint8_t cl = temp[9];
                uint8_t cs = temp[10];
                uint8_t cp = temp[11];

                parseResult->addEvent(static_cast<EventType>(messageType), pc, cardId, {
                    {"origin", {
                       {"controller", pc},
                       {"location", pl},
                       {"sequence", ps},
                       {"position", pp}
                    }},
                    {"destination", {
                        {"controller", cc},
                        {"location", cl},
                        {"sequence", cs},
                        {"position", cp}
                    }}
                });
                reader.moveCursorForward(12);
                break;
            }

            case MSG_POS_CHANGE: {
                reader.moveCursorForward(9);
                break;
            }

            case MSG_SET: {
                reader.moveCursorForward(8);
                break;
            }

            case MSG_SWAP: {
                reader.moveCursorForward(16);
                break;
            }

            case MSG_FIELD_DISABLED: {
                reader.moveCursorForward(4);
                break;
            }

            case MSG_SPSUMMONING:
            case MSG_SUMMONING:
            case MSG_FLIPSUMMONING: {
                auto cardId = reader.read<uint32_t>();
                player = reader.read<int8_t>();
                parseResult->addEvent(static_cast<EventType>(messageType), player, cardId);

                reader.moveCursorForward(3);
                break;
            }

            case MSG_SUMMONED:
            case MSG_SPSUMMONED:
            case MSG_FLIPSUMMONED: {
                break;
            }

            case MSG_CHAINING: {
                auto cardId = reader.read<uint32_t>();
                temp = reader.current();
                uint8_t pc = temp[0];
                uint8_t pl = temp[1];
                uint8_t ps = temp[2];
                uint8_t pp = temp[3];
                uint8_t cc = temp[4];
                uint8_t cl = temp[5];
                uint8_t cs = temp[6];
                uint8_t cp = temp[7];

                parseResult->addEvent(static_cast<EventType>(messageType), pc, cardId, {
                    {"triggering", {
                        {"controller", pc},
                        {"location", pl},
                        {"sequence", ps},
                        {"position", pp}
                    }},
                    {"location", {
                        {"controller", cc},
                        {"location", cl},
                        {"sequence", cs},
                        {"position", cp}
                    }}
                });

                reader.moveCursorForward(12);
                break;
            }

            case MSG_CHAIN_END: {
                break;
            }

            case MSG_CHAINED:
            case MSG_CHAIN_SOLVING:
            case MSG_CHAIN_SOLVED:
            case MSG_CHAIN_NEGATED:
            case MSG_CHAIN_DISABLED:
            case MSG_REFRESH_DECK: {
                reader.moveCursorForward();
                break;
            }

            case MSG_CARD_SELECTED:
            case MSG_RANDOM_SELECTED: {
                player = reader.read<int8_t>();
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 4);
                break;
            }

            case MSG_BECOME_TARGET: {
                count = reader.read<int8_t>();
                reader.moveCursorForward(count * 4);
                break;
            }

            case MSG_DRAW: {
                player = reader.read<int8_t>();
                count = reader.read<int8_t>();
                for (int8_t i = 0; i < count; ++i) {
                    parseResult->addEvent(static_cast<EventType>(messageType), player, reader.read< uint32_t>());
                }
                break;
            }

            case MSG_DAMAGE:
            case MSG_RECOVER: {
                reader.moveCursorForward(5);
                break;
            }

            case MSG_EQUIP: {
                reader.moveCursorForward(8);
                break;
            }

            case MSG_LPUPDATE: {
                reader.moveCursorForward(5);
                break;
            }

            case MSG_UNEQUIP: {
                reader.moveCursorForward(4);
                break;
            }

            case MSG_CARD_TARGET:
            case MSG_CANCEL_TARGET: {
                reader.moveCursorForward(8);
                break;
            }

            case MSG_PAY_LPCOST: {
                reader.moveCursorForward(5);
                break;
            }

            case MSG_ADD_COUNTER:
            case MSG_REMOVE_COUNTER: {
                reader.moveCursorForward(7);
                break;
            }

            case MSG_ATTACK: {
                reader.moveCursorForward(8);
                break;
            }

            case MSG_BATTLE: {
                reader.moveCursorForward(26);
                break;
            }

            case MSG_ATTACK_DISABLED:
            case MSG_DAMAGE_STEP_START:
            case MSG_DAMAGE_STEP_END: {
                break;
            }

            case MSG_MISSED_EFFECT: {
                reader.moveCursorForward(8);
                break;
            }

            case MSG_TOSS_COIN:
            case MSG_TOSS_DICE: {
                player = reader.read<int8_t>();
                count = reader.read<int8_t>();
                reader.moveCursorForward(count);
                break;
            }

            case MSG_ROCK_PAPER_SCISSORS: {
                player = reader.read<int8_t>();
                return this->readResponse();
            }

            case MSG_HAND_RES: {
                reader.moveCursorForward(1);
                break;
            }

            case MSG_ANNOUNCE_RACE:
            case MSG_ANNOUNCE_ATTRIB: {
                player = reader.read<int8_t>();
                reader.moveCursorForward(5);
                return this->readResponse();
            }

            case MSG_ANNOUNCE_CARD:

            case MSG_ANNOUNCE_NUMBER: {
                player = reader.read<int8_t>();
                count = reader.read<uint8_t>();
                reader.moveCursorForward(4 * count);
                return this->readResponse();
            }

            case MSG_CARD_HINT: {
                reader.moveCursorForward(9);
                break;
            }

            case MSG_PLAYER_HINT: {
                reader.moveCursorForward(6);
                break;
            }

            case MSG_MATCH_KILL: {
                reader.moveCursorForward(4);
                break;
            }

            case MSG_TAG_SWAP: {
                temp = reader.current();
                player = temp[0];
                reader.moveCursorForward(temp[2] * 4 + temp[4] * 4 + 9);
                break;
            }

            case MSG_RELOAD_FIELD: {
                reader.moveCursorForward();
                for (int p = 0; p < 2; ++p) {
                    reader.moveCursorForward(4);
                    for (int seq = 0; seq < 7; ++seq) {
                        auto val = reader.read<int8_t>();
                        if (val)
                            reader.moveCursorForward(2);
                    }
                    for (int seq = 0; seq < 8; ++seq) {
                        auto val = reader.read<int8_t>();
                        if (val)
                            reader.moveCursorForward();
                    }
                    reader.moveCursorForward(6);
                }
                reader.moveCursorForward();
                break;
            }

            case MSG_AI_NAME: {
                int len = reader.read<int16_t>();
                reader.moveCursorForward(len + 1);
                break;
            }

            case MSG_SHOW_HINT: {
                int len = reader.read<int16_t>();
                reader.moveCursorForward(len + 1);
                break;
            }
        }
    }

    return true;
}