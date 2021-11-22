#include "common.hpp"
#include "parse-result.hpp"

#include <utility>


void ParseResult::addEvent(EventType type, uint8_t player, uint32_t relatedCardId) {
    auto* cardData = new CardData();
    auto* event = new Event();
    event->type = type;
    event->player = player;
    event->relatedCard = cardData;

    if (!CardManager::getInstance()->get(relatedCardId, cardData)) {
        delete cardData;
        delete event;

        return;
    }

    this->events.push_back(event);
}
void ParseResult::addEvent(EventType type, uint8_t player, uint32_t relatedCardId, nlohmann::json data) {
    auto* cardData = new CardData();
    auto* event = new Event();
    event->type = type;
    event->player = player;
    event->relatedCard = cardData;
    event->data = std::move(data);

    if (!CardManager::getInstance()->get(relatedCardId, cardData)) {
        delete cardData;
        delete event;

        return;
    }

    this->events.push_back(event);
}

ParseResult::ParseResult() : events() {}
ParseResult::~ParseResult() {
    for (const auto& item : this->events) {
        delete item;
    }

    this->events.clear();
}

nlohmann::json ParseResult::toJSON() {
    if (this->json.empty()) {
        this->generateJSON();
    }

    return this->json;
}

void ParseResult::generateJSON() {
    for (const auto& item : this->events) {
        nlohmann::json event;
        event["type"] = item->type;
        event["player"] = item->player;
        event["relatedCardId"] = item->relatedCard->code;
        if (!item->data.is_null()) {
            event["data"] = item->data;
        }

        this->json["events"].push_back(event);
    }
}
