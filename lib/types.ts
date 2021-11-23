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

interface RetryEvent {
    type: ReplayMessageType.MSG_RETRY;
}
interface HintEvent {
    type: ReplayMessageType.MSG_HINT;
}
interface WaitingEvent {
    type: ReplayMessageType.MSG_WAITING;
}
interface StartEvent {
    type: ReplayMessageType.MSG_START;
}
interface WinEvent {
    type: ReplayMessageType.MSG_WIN;
}
interface UpdateDataEvent {
    type: ReplayMessageType.MSG_UPDATE_DATA;
}
interface UpdateCardEvent {
    type: ReplayMessageType.MSG_UPDATE_CARD;
}
interface RequestDeckEvent {
    type: ReplayMessageType.MSG_REQUEST_DECK;
}
interface SelectBattlecmdEvent {
    type: ReplayMessageType.MSG_SELECT_BATTLECMD;
}
interface SelectIdlecmdEvent {
    type: ReplayMessageType.MSG_SELECT_IDLECMD;
}
interface SelectEffectynEvent {
    type: ReplayMessageType.MSG_SELECT_EFFECTYN;
}
interface SelectYesnoEvent {
    type: ReplayMessageType.MSG_SELECT_YESNO;
}
interface SelectOptionEvent {
    type: ReplayMessageType.MSG_SELECT_OPTION;
}
interface SelectCardEvent {
    type: ReplayMessageType.MSG_SELECT_CARD;
}
interface SelectChainEvent {
    type: ReplayMessageType.MSG_SELECT_CHAIN;
}
interface SelectPlaceEvent {
    type: ReplayMessageType.MSG_SELECT_PLACE;
}
interface SelectPositionEvent {
    type: ReplayMessageType.MSG_SELECT_POSITION;
}
interface SelectTributeEvent {
    type: ReplayMessageType.MSG_SELECT_TRIBUTE;
}
interface SortChainEvent {
    type: ReplayMessageType.MSG_SORT_CHAIN;
}
interface SelectCounterEvent {
    type: ReplayMessageType.MSG_SELECT_COUNTER;
}
interface SelectSumEvent {
    type: ReplayMessageType.MSG_SELECT_SUM;
}
interface SelectDisfieldEvent {
    type: ReplayMessageType.MSG_SELECT_DISFIELD;
}
interface SortCardEvent {
    type: ReplayMessageType.MSG_SORT_CARD;
}
interface SelectUnselectCardEvent {
    type: ReplayMessageType.MSG_SELECT_UNSELECT_CARD;
}
interface ConfirmDecktopEvent {
    type: ReplayMessageType.MSG_CONFIRM_DECKTOP;
}
interface ConfirmCardsEvent {
    type: ReplayMessageType.MSG_CONFIRM_CARDS;
}
interface ShuffleDeckEvent {
    type: ReplayMessageType.MSG_SHUFFLE_DECK;
}
interface ShuffleHandEvent {
    type: ReplayMessageType.MSG_SHUFFLE_HAND;
}
interface RefreshDeckEvent {
    type: ReplayMessageType.MSG_REFRESH_DECK;
}
interface SwapGraveDeckEvent {
    type: ReplayMessageType.MSG_SWAP_GRAVE_DECK;
}
interface ShuffleSetCardEvent {
    type: ReplayMessageType.MSG_SHUFFLE_SET_CARD;
}
interface ReverseDeckEvent {
    type: ReplayMessageType.MSG_REVERSE_DECK;
}
interface DeckTopEvent {
    type: ReplayMessageType.MSG_DECK_TOP;
}
interface ShuffleExtraEvent {
    type: ReplayMessageType.MSG_SHUFFLE_EXTRA;
}
interface NewTurnEvent {
    type: ReplayMessageType.MSG_NEW_TURN;
}
interface NewPhaseEvent {
    type: ReplayMessageType.MSG_NEW_PHASE;
}
interface ConfirmExtratopEvent {
    type: ReplayMessageType.MSG_CONFIRM_EXTRATOP;
}
interface MoveEvent {
    type: ReplayMessageType.MSG_MOVE;
}
interface PosChangeEvent {
    type: ReplayMessageType.MSG_POS_CHANGE;
}
interface SetEvent {
    type: ReplayMessageType.MSG_SET;
}
interface SwapEvent {
    type: ReplayMessageType.MSG_SWAP;
}
interface FieldDisabledEvent {
    type: ReplayMessageType.MSG_FIELD_DISABLED;
}
interface SummoningEvent {
    type: ReplayMessageType.MSG_SUMMONING;
}
interface SummonedEvent {
    type: ReplayMessageType.MSG_SUMMONED;
}
interface SpsummoningEvent {
    type: ReplayMessageType.MSG_SPSUMMONING;
}
interface SpsummonedEvent {
    type: ReplayMessageType.MSG_SPSUMMONED;
}
interface FlipsummoningEvent {
    type: ReplayMessageType.MSG_FLIPSUMMONING;
}
interface FlipsummonedEvent {
    type: ReplayMessageType.MSG_FLIPSUMMONED;
}
interface ChainingEvent {
    type: ReplayMessageType.MSG_CHAINING;
}
interface ChainedEvent {
    type: ReplayMessageType.MSG_CHAINED;
}
interface ChainSolvingEvent {
    type: ReplayMessageType.MSG_CHAIN_SOLVING;
}
interface ChainSolvedEvent {
    type: ReplayMessageType.MSG_CHAIN_SOLVED;
}
interface ChainEndEvent {
    type: ReplayMessageType.MSG_CHAIN_END;
}
interface ChainNegatedEvent {
    type: ReplayMessageType.MSG_CHAIN_NEGATED;
}
interface ChainDisabledEvent {
    type: ReplayMessageType.MSG_CHAIN_DISABLED;
}
interface CardSelectedEvent {
    type: ReplayMessageType.MSG_CARD_SELECTED;
}
interface RandomSelectedEvent {
    type: ReplayMessageType.MSG_RANDOM_SELECTED;
}
interface BecomeTargetEvent {
    type: ReplayMessageType.MSG_BECOME_TARGET;
}
interface DrawEvent {
    type: ReplayMessageType.MSG_DRAW;
}
interface DamageEvent {
    type: ReplayMessageType.MSG_DAMAGE;
}
interface RecoverEvent {
    type: ReplayMessageType.MSG_RECOVER;
}
interface EquipEvent {
    type: ReplayMessageType.MSG_EQUIP;
}
interface LpupdateEvent {
    type: ReplayMessageType.MSG_LPUPDATE;
}
interface UnequipEvent {
    type: ReplayMessageType.MSG_UNEQUIP;
}
interface CardTargetEvent {
    type: ReplayMessageType.MSG_CARD_TARGET;
}
interface CancelTargetEvent {
    type: ReplayMessageType.MSG_CANCEL_TARGET;
}
interface PayLpcostEvent {
    type: ReplayMessageType.MSG_PAY_LPCOST;
}
interface AddCounterEvent {
    type: ReplayMessageType.MSG_ADD_COUNTER;
}
interface RemoveCounterEvent {
    type: ReplayMessageType.MSG_REMOVE_COUNTER;
}
interface AttackEvent {
    type: ReplayMessageType.MSG_ATTACK;
}
interface BattleEvent {
    type: ReplayMessageType.MSG_BATTLE;
}
interface AttackDisabledEvent {
    type: ReplayMessageType.MSG_ATTACK_DISABLED;
}
interface DamageStepStartEvent {
    type: ReplayMessageType.MSG_DAMAGE_STEP_START;
}
interface DamageStepEndEvent {
    type: ReplayMessageType.MSG_DAMAGE_STEP_END;
}
interface MissedEffectEvent {
    type: ReplayMessageType.MSG_MISSED_EFFECT;
}
interface BeChainTargetEvent {
    type: ReplayMessageType.MSG_BE_CHAIN_TARGET;
}
interface CreateRelationEvent {
    type: ReplayMessageType.MSG_CREATE_RELATION;
}
interface ReleaseRelationEvent {
    type: ReplayMessageType.MSG_RELEASE_RELATION;
}
interface TossCoinEvent {
    type: ReplayMessageType.MSG_TOSS_COIN;
}
interface TossDiceEvent {
    type: ReplayMessageType.MSG_TOSS_DICE;
}
interface RockPaperScissorsEvent {
    type: ReplayMessageType.MSG_ROCK_PAPER_SCISSORS;
}
interface HandResEvent {
    type: ReplayMessageType.MSG_HAND_RES;
}
interface AnnounceRaceEvent {
    type: ReplayMessageType.MSG_ANNOUNCE_RACE;
}
interface AnnounceAttribEvent {
    type: ReplayMessageType.MSG_ANNOUNCE_ATTRIB;
}
interface AnnounceCardEvent {
    type: ReplayMessageType.MSG_ANNOUNCE_CARD;
}
interface AnnounceNumberEvent {
    type: ReplayMessageType.MSG_ANNOUNCE_NUMBER;
}
interface CardHintEvent {
    type: ReplayMessageType.MSG_CARD_HINT;
}
interface TagSwapEvent {
    type: ReplayMessageType.MSG_TAG_SWAP;
}
interface ReloadFieldEvent {
    type: ReplayMessageType.MSG_RELOAD_FIELD;
}
interface AiNameEvent {
    type: ReplayMessageType.MSG_AI_NAME;
}
interface ShowHintEvent {
    type: ReplayMessageType.MSG_SHOW_HINT;
}
interface PlayerHintEvent {
    type: ReplayMessageType.MSG_PLAYER_HINT;
}
interface MatchKillEvent {
    type: ReplayMessageType.MSG_MATCH_KILL;
}
interface CustomMsgEvent {
    type: ReplayMessageType.MSG_CUSTOM_MSG;
}

export type ReplayEvent =
    | RetryEvent
    | HintEvent
    | WaitingEvent
    | StartEvent
    | WinEvent
    | UpdateDataEvent
    | UpdateCardEvent
    | RequestDeckEvent
    | SelectBattlecmdEvent
    | SelectIdlecmdEvent
    | SelectEffectynEvent
    | SelectYesnoEvent
    | SelectOptionEvent
    | SelectCardEvent
    | SelectChainEvent
    | SelectPlaceEvent
    | SelectPositionEvent
    | SelectTributeEvent
    | SortChainEvent
    | SelectCounterEvent
    | SelectSumEvent
    | SelectDisfieldEvent
    | SortCardEvent
    | SelectUnselectCardEvent
    | ConfirmDecktopEvent
    | ConfirmCardsEvent
    | ShuffleDeckEvent
    | ShuffleHandEvent
    | RefreshDeckEvent
    | SwapGraveDeckEvent
    | ShuffleSetCardEvent
    | ReverseDeckEvent
    | DeckTopEvent
    | ShuffleExtraEvent
    | NewTurnEvent
    | NewPhaseEvent
    | ConfirmExtratopEvent
    | MoveEvent
    | PosChangeEvent
    | SetEvent
    | SwapEvent
    | FieldDisabledEvent
    | SummoningEvent
    | SummonedEvent
    | SpsummoningEvent
    | SpsummonedEvent
    | FlipsummoningEvent
    | FlipsummonedEvent
    | ChainingEvent
    | ChainedEvent
    | ChainSolvingEvent
    | ChainSolvedEvent
    | ChainEndEvent
    | ChainNegatedEvent
    | ChainDisabledEvent
    | CardSelectedEvent
    | RandomSelectedEvent
    | BecomeTargetEvent
    | DrawEvent
    | DamageEvent
    | RecoverEvent
    | EquipEvent
    | LpupdateEvent
    | UnequipEvent
    | CardTargetEvent
    | CancelTargetEvent
    | PayLpcostEvent
    | AddCounterEvent
    | RemoveCounterEvent
    | AttackEvent
    | BattleEvent
    | AttackDisabledEvent
    | DamageStepStartEvent
    | DamageStepEndEvent
    | MissedEffectEvent
    | BeChainTargetEvent
    | CreateRelationEvent
    | ReleaseRelationEvent
    | TossCoinEvent
    | TossDiceEvent
    | RockPaperScissorsEvent
    | HandResEvent
    | AnnounceRaceEvent
    | AnnounceAttribEvent
    | AnnounceCardEvent
    | AnnounceNumberEvent
    | CardHintEvent
    | TagSwapEvent
    | ReloadFieldEvent
    | AiNameEvent
    | ShowHintEvent
    | PlayerHintEvent
    | MatchKillEvent
    | CustomMsgEvent;

export interface ReplayParseResult {
    events: ReplayEvent;
}
