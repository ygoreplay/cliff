#ifndef CLIFF_CARD_MANAGER_HPP
#define CLIFF_CARD_MANAGER_HPP

#define TYPE_MONSTER		0x1			//
#define TYPE_SPELL			0x2			//
#define TYPE_TRAP			0x4			//
#define TYPE_NORMAL			0x10		//
#define TYPE_EFFECT			0x20		//
#define TYPE_FUSION			0x40		//
#define TYPE_RITUAL			0x80		//
#define TYPE_TRAPMONSTER	0x100		//
#define TYPE_SPIRIT			0x200		//
#define TYPE_UNION			0x400		//
#define TYPE_DUAL			0x800		//
#define TYPE_TUNER			0x1000		//
#define TYPE_SYNCHRO		0x2000		//
#define TYPE_TOKEN			0x4000		//
#define TYPE_QUICKPLAY		0x10000		//
#define TYPE_CONTINUOUS		0x20000		//
#define TYPE_EQUIP			0x40000		//
#define TYPE_FIELD			0x80000		//
#define TYPE_COUNTER		0x100000	//
#define TYPE_FLIP			0x200000	//
#define TYPE_TOON			0x400000	//
#define TYPE_XYZ			0x800000	//
#define TYPE_PENDULUM		0x1000000	//
#define TYPE_SPSUMMON		0x2000000	//
#define TYPE_LINK			0x4000000	//

struct CardData {
    unsigned int code;
    unsigned int alias;
    unsigned long long setcode;
    unsigned int type;
    unsigned int level;
    unsigned int attribute;
    unsigned int race;
    int attack;
    int defense;
    unsigned int lscale;
    unsigned int rscale;
    unsigned int linkMarker;
};

struct CardDataC {
    unsigned int code;
    unsigned int alias;
    unsigned long long setcode;
    unsigned int type;
    unsigned int level;
    unsigned int attribute;
    unsigned int race;
    int attack;
    int defense;
    unsigned int lscale;
    unsigned int rscale;
    unsigned int linkMarker;
    unsigned int ot;
    unsigned int category;
};

class CardManager {
private:
    static CardManager* instance;

public:
    static CardManager* getInstance();

private:
    CardManager();
    ~CardManager();

public:
    bool initialize(const std::string& databasePath);

public:
    bool get(uint32_t id, CardData* dest);

private:
    std::unordered_map<uint32_t, CardDataC*> cards;
};

#endif // CLIFF_CARD_MANAGER_HPP
