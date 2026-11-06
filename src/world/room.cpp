#include "room.hpp"
#include <memory>
#include <print>
#include <unordered_map>

#include "../game/sense.hpp"

std::unordered_map<std::string, ActionVerb> object_action = {
    {"get", ActionVerb::get},
    {"drop", ActionVerb::drop},
    {"use", ActionVerb::use}};
std::unordered_map<std::string, SenseVerb> object_sense = {
    {"examine", SenseVerb::examine}, {"look", SenseVerb::look},
    {"feel", SenseVerb::feel},       {"listen", SenseVerb::listen},
    {"smell", SenseVerb::smell},     {"taste", SenseVerb::taste}};

bool Room::init(GameState &state) {
    std::shared_ptr<Room> current_room = std::make_shared<Room>();
    if (current_room == nullptr) {
        std::cerr << "\nError creating room ptr..\n";
    }

    return true;
}

bool Room::is_alias(const Command &command, Object &item) {
    for (auto alias : item.get_aliases()) {
        std::cout << "\n" << alias << std::endl;
        std::cout << "\n" << command.target << std::endl;
        if (alias == command.target) {
            return true;
        }
    }
    return false;
}

std::string Room::get_generic() { return generic_desc.at(light_env.light); }
std::string Room::get_examine() { return examine_desc.at(light_env.light); }
std::string Room::get_look() {
    std::println("Light_lvl: {}.", light_env.light);
    return look_desc.at(static_cast<int>(light_env.light));
}

std::string Room::find_object_info(const Command &command) {
    std::cout << "find_object_info: ";
    std::string target = "";
    for (auto &item : room_items) {
        std::string alias_check = item->get_alias(command.target);
        if (alias_check == command.target) {
            switch (object_sense.at(command.verb)) {
            case SenseVerb::examine: {
                return item->examine_info(light_env.light);
                break;
            }
            case SenseVerb::look: {
                return item->sight_info(light_env.light);
                break;
            }
            case SenseVerb::feel: {
                return item->touch_info();
                break;
            }
            case SenseVerb::listen: {
                return item->sound_info();
                break;
            }
            case SenseVerb::smell: {
                return item->smell_info();
                break;
            }
            case SenseVerb::taste: {
                return item->taste_info();
                break;
            }
            default:
                return "You don't see it here.";
            }
        }
    }
    return "It doesn't seem to be here.";
}

int Room::find_object_get(const std::string &verb,
                          const std::string &alias_check) {
    std::string target{};
    int item_deleted{};
    std::println("ActionVerb::get in room, searching item: {}.", alias_check);
    for (auto &item : room_items) {
        if (alias_check != "none" && item->get_type() == alias_check) {
            if (item->is_takeable()) {
                item_deleted = item->get_id();
                std::println("ActionVerb::get: {}", item->get_name());
            } else {
                item_deleted = -1;
            }
            break;
        }
        item_deleted = -1;
    }
    if (item_deleted != -1) {

        std::erase_if(room_items, [item_deleted](const auto &item) {
            return item->is_takeable() && item->get_id() == item_deleted;
        });
    }
    return item_deleted;
}

void Room::find_object_drop(Object *dropped_item) {
    room_items.emplace_back(dropped_item);
}
