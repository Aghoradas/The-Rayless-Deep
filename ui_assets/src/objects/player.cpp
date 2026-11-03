#include "player.hpp"
#include "../app/app_state.hpp"
#include "game/game_event.hpp"
#include <memory>

void Player::init(GameState &game_state) {
    set_location(game_state.rooms.at(0));
}

std::string Player::get_description(Verb verb_command) {
    switch (verb_command) {
    case Verb::examine: {
        return examine;
        break;
    }
    case Verb::look: {
        return description;
        break;
    }
    case Verb::smell: {
        return smell;
        break;
    }
    case Verb::taste: {
        return taste;
        break;
    }
    case Verb::touch: {
        return touch;
        break;
    }
    case Verb::hearing: {
        return sound;
    }
    default: {
        return "idk..";
        break;
    }
    }
}

std::shared_ptr<Room> Player::location() const { return location_; }

void Player::set_location(std::shared_ptr<Room> room) { location_ = room; }

void Player::get_object(Object *item) {
    inventory.emplace_back(std::ref(item));
}

int Player::drop_object(const std::string &dropped_item) {
    int item_deleted{};
    for (auto &item : inventory) {
        std::string alias_check{item->get_alias(dropped_item)};
        if (alias_check != "none") {
            item_deleted = item->get_id();
            break;
        }
        item_deleted = -1;
    }
    if (item_deleted != -1) {
        std::erase_if(inventory, [item_deleted](const auto &item) {
            return item->is_takeable() && item->get_id() == item_deleted;
        });
    }
    return item_deleted;
}
