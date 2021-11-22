#include "common.hpp"
#include "card-manager.hpp"

CardManager* CardManager::instance = nullptr;

CardManager* CardManager::getInstance() {
    if (CardManager::instance == nullptr) {
        CardManager::instance = new CardManager();
    }

    return CardManager::instance;
}

CardManager::CardManager() = default;
CardManager::~CardManager() {
    for (auto const& [cardId, card] : this->cards) {
        delete card;
    }
}

bool CardManager::initialize(const std::string& databasePath) {
    try {
        SQLite::Database db(databasePath);
        SQLite::Statement query(db, "SELECT * FROM datas");

        while (query.executeStep()) {
            auto* card = new CardDataC();
            card->code = query.getColumn(0);
            card->ot = query.getColumn(1);
            card->alias = query.getColumn(2);
            card->setcode = query.getColumn(3).operator long long();
            card->type = query.getColumn(4);
            card->attack = query.getColumn(5);
            card->defense = query.getColumn(6);
            if (card->type & TYPE_LINK) {
                card->linkMarker = card->defense;
                card->defense = 0;
            } else {
                card->linkMarker = 0;
            }

            uint32_t level = query.getColumn(7);
            card->level = level & 0xFF;
            card->lscale = (level >> 24) & 0xFF;
            card->rscale = (level >> 16) & 0xFF;

            card->race = query.getColumn(8);
            card->attribute = query.getColumn(9);
            card->category = query.getColumn(10);

            this->cards[card->code] = card;
        }

        return true;
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return false;
}

bool CardManager::get(uint32_t id, CardData* data) {
    auto iter = this->cards.find(id);
    if (iter == this->cards.end()) {
        memset(data, 0, sizeof(CardData));
        return false;
    }

    if (data) {
        data->code = iter->second->code;
        data->alias = iter->second->alias;
        data->setcode = iter->second->setcode;
        data->type = iter->second->type;
        data->level = iter->second->level;
        data->attribute = iter->second->attribute;
        data->race = iter->second->race;
        data->attack = iter->second->attack;
        data->defense = iter->second->defense;
        data->lscale = iter->second->lscale;
        data->rscale = iter->second->rscale;
        data->linkMarker = iter->second->linkMarker;
    }

    return true;
}
