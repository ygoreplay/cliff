const cliff = require("bindings")("cliff");

export enum CardLocation {
    Deck = 0x01,
    Hand = 0x02,
    MonsterZone = 0x04,
    SpellZone = 0x08,
    Grave = 0x10,
    Removed = 0x20,
    Extra = 0x40,
    Overlay = 0x80,
    OnField = 0x0c,
    FieldZone = 0x100,
    PendulumZone = 0x200,
    DeckBot = 0x10001,
    DeckShf = 0x20001,
}
export enum ReplayMessageType {
    MSG_RETRY = 1,
    MSG_HINT = 2,
    MSG_WAITING = 3,
    MSG_START = 4,
    MSG_WIN = 5,
    MSG_UPDATE_DATA = 6,
    MSG_UPDATE_CARD = 7,
    MSG_REQUEST_DECK = 8,
    MSG_SELECT_BATTLECMD = 10,
    MSG_SELECT_IDLECMD = 11,
    MSG_SELECT_EFFECTYN = 12,
    MSG_SELECT_YESNO = 13,
    MSG_SELECT_OPTION = 14,
    MSG_SELECT_CARD = 15,
    MSG_SELECT_CHAIN = 16,
    MSG_SELECT_PLACE = 18,
    MSG_SELECT_POSITION = 19,
    MSG_SELECT_TRIBUTE = 20,
    MSG_SORT_CHAIN = 21,
    MSG_SELECT_COUNTER = 22,
    MSG_SELECT_SUM = 23,
    MSG_SELECT_DISFIELD = 24,
    MSG_SORT_CARD = 25,
    MSG_SELECT_UNSELECT_CARD = 26,
    MSG_CONFIRM_DECKTOP = 30,
    MSG_CONFIRM_CARDS = 31,
    MSG_SHUFFLE_DECK = 32,
    MSG_SHUFFLE_HAND = 33,
    MSG_REFRESH_DECK = 34,
    MSG_SWAP_GRAVE_DECK = 35,
    MSG_SHUFFLE_SET_CARD = 36,
    MSG_REVERSE_DECK = 37,
    MSG_DECK_TOP = 38,
    MSG_SHUFFLE_EXTRA = 39,
    MSG_NEW_TURN = 40,
    MSG_NEW_PHASE = 41,
    MSG_CONFIRM_EXTRATOP = 42,
    MSG_MOVE = 50,
    MSG_POS_CHANGE = 53,
    MSG_SET = 54,
    MSG_SWAP = 55,
    MSG_FIELD_DISABLED = 56,
    MSG_SUMMONING = 60,
    MSG_SUMMONED = 61,
    MSG_SPSUMMONING = 62,
    MSG_SPSUMMONED = 63,
    MSG_FLIPSUMMONING = 64,
    MSG_FLIPSUMMONED = 65,
    MSG_CHAINING = 70,
    MSG_CHAINED = 71,
    MSG_CHAIN_SOLVING = 72,
    MSG_CHAIN_SOLVED = 73,
    MSG_CHAIN_END = 74,
    MSG_CHAIN_NEGATED = 75,
    MSG_CHAIN_DISABLED = 76,
    MSG_CARD_SELECTED = 80,
    MSG_RANDOM_SELECTED = 81,
    MSG_BECOME_TARGET = 83,
    MSG_DRAW = 90,
    MSG_DAMAGE = 91,
    MSG_RECOVER = 92,
    MSG_EQUIP = 93,
    MSG_LPUPDATE = 94,
    MSG_UNEQUIP = 95,
    MSG_CARD_TARGET = 96,
    MSG_CANCEL_TARGET = 97,
    MSG_PAY_LPCOST = 100,
    MSG_ADD_COUNTER = 101,
    MSG_REMOVE_COUNTER = 102,
    MSG_ATTACK = 110,
    MSG_BATTLE = 111,
    MSG_ATTACK_DISABLED = 112,
    MSG_DAMAGE_STEP_START = 113,
    MSG_DAMAGE_STEP_END = 114,
    MSG_MISSED_EFFECT = 120,
    MSG_BE_CHAIN_TARGET = 121,
    MSG_CREATE_RELATION = 122,
    MSG_RELEASE_RELATION = 123,
    MSG_TOSS_COIN = 130,
    MSG_TOSS_DICE = 131,
    MSG_ROCK_PAPER_SCISSORS = 132,
    MSG_HAND_RES = 133,
    MSG_ANNOUNCE_RACE = 140,
    MSG_ANNOUNCE_ATTRIB = 141,
    MSG_ANNOUNCE_CARD = 142,
    MSG_ANNOUNCE_NUMBER = 143,
    MSG_CARD_HINT = 160,
    MSG_TAG_SWAP = 161,
    MSG_RELOAD_FIELD = 162,
    MSG_AI_NAME = 163,
    MSG_SHOW_HINT = 164,
    MSG_PLAYER_HINT = 165,
    MSG_MATCH_KILL = 170,
    MSG_CUSTOM_MSG = 180,
}
export interface LocationInformation {
    player: number;
    location: CardLocation;
    sequence: number;
    position: number;
}

export interface PlayerEvent {
    player: number;
}
export interface CardEvent {
    relatedCardId: number;
}

export interface MoveEvent extends PlayerEvent, CardEvent {
    type: ReplayMessageType.MSG_MOVE;
    data: {
        origin: LocationInformation;
        destination: LocationInformation;
    };
}
export interface FlipSummonedEvent extends PlayerEvent, CardEvent {
    type: ReplayMessageType.MSG_FLIPSUMMONED;
}
export interface FlipSummoningEvent extends PlayerEvent, CardEvent {
    type: ReplayMessageType.MSG_FLIPSUMMONING;
}
export interface SpecialSummonedEvent extends PlayerEvent, CardEvent {
    type: ReplayMessageType.MSG_SPSUMMONED;
}
export interface SpecialSummoningEvent extends PlayerEvent, CardEvent {
    type: ReplayMessageType.MSG_SPSUMMONING;
}
export interface SummonedEvent extends PlayerEvent, CardEvent {
    type: ReplayMessageType.MSG_SUMMONED;
}
export interface SummoningEvent extends PlayerEvent, CardEvent {
    type: ReplayMessageType.MSG_SUMMONING;
}

export type ReplayEvent =
    | MoveEvent
    | FlipSummonedEvent
    | FlipSummoningEvent
    | SpecialSummonedEvent
    | SpecialSummoningEvent
    | SummonedEvent
    | SummoningEvent;

interface ReplayData {
    event: ReplayEvent[];
}

export function initialize(databasePath: string, scriptsDirectoryPath: string) {
    cliff.initialize(databasePath, scriptsDirectoryPath);
}
export function parse(replayFilePath: string): ReplayData {
    return cliff.parse(replayFilePath);
}
