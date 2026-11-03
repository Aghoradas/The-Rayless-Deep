#include "game_handler.hpp"
#include <flat_map>
#include <memory>
#include <print>
#include <unordered_map>
#include <vector>

#include "../objects/player.hpp"
#include "app/app_state.hpp"
#include "game_event.hpp"
#include "objects/components/comp_system.hpp"
#include "objects/object.hpp"
#include "ui/ui_port.hpp"

static inline std::unordered_map<std::string, Utils> utils_handler{
    {"menu", Utils::menu}, {"inventory", Utils::inventory}};

static inline std::unordered_map<std::string, Verb> verb_handler{
    {"examine", Verb::examine}, {"look", Verb::look},
    {"smell", Verb::smell},     {"taste", Verb::taste},
    {"feel", Verb::touch},      {"listen", Verb::hearing},
    {"get", Verb::get},         {"drop", Verb::drop},
    {"use", Verb::use},         {"move", Verb::move}};

static inline std::flat_map<std::string, CompType> comptype_lookup = {
    {"light", CompType::light}, {"use", CompType::usage}};

std::string GameHandler::command_handler(GameState &game_state,
                                         ui::GameText &game_text,
                                         Command &command) {
    Player &player{game_state.player};
    if (command.verb.empty()) {
        return handle_error(player, command);
    }

    if (verb_handler.find(command.verb) == 0 &&
        utils_handler.find(command.verb) == 0) {
        return handle_error(player, command);
    }

    // Utilities Handler
    if (utils_handler.contains(command.verb)) {
        switch (utils_handler.at(command.verb)) {
        case Utils::menu: {
            return "We need a way back to the menu, I guess.";
            break;
        }
        case Utils::inventory: {
            return handle_inventory(game_text, player);
            break;
        }
        default: {
            break;
        }
        };
    }

    // Verb Handler
    switch (verb_handler.at(command.verb)) {
    case Verb::examine: {
        return handle_examine(player, command);
        break;
    }
    case Verb::look: {
        return handle_look(player, command);
        break;
    }
    case Verb::smell: {
        return handle_smell(player, command);
        break;
    }
    case Verb::taste: {
        return handle_taste(player, command);
        break;
    }
    case Verb::touch: {
        return handle_touch(player, command);
        break;
    }
    case Verb::hearing: {
        return handle_hearing(player, command);
        break;
    }
    case Verb::get: {
        return handle_get(game_state, command);
        break;
    }
    case Verb::drop: {
        return handle_drop(game_state, command.target);
        break;
    }
    case Verb::use: {
        return handle_use(player, command);
        break;
    }
    case Verb::move: {
        handle_move(player, game_state.rooms, command);
        std::println("player.location(): {}", player.location()->room_name);
        return "I'm imprisoned, with no way..it seems. Where could I move?";
        break;
    }
    default: {
        return "hmm..";
    }
    };
}

std::string GameHandler::handle_examine(Player &player,
                                        const Command &command) const {
    if (command.target.empty()) {

        return player.location()->get_examine();
    }
    if (command.target == "self") {
        return player.get_description(Verb::examine);
    }

    return player.location()->find_object_info(command);
    return "You don't see anything called " + command.target + ".";
}

std::string GameHandler::handle_look(Player &player,
                                     const Command &command) const {
    if (command.target.empty()) {

        return player.location()->get_look();
    }
    if (command.target == "self") {
        return player.get_description(Verb::look);
    }

    return player.location()->find_object_info(command);
    return "You don't see anything called " + command.target + ".";
}

std::string GameHandler::handle_smell(Player &player,
                                      const Command &command) const {
    if (command.target.empty()) {
        return player.location()->smell_desc;
    }
    if (command.target == "self") {
        return player.get_description(Verb::smell);
    }
    return player.location()->find_object_info(command);
    return "There's nothing called " + command.target + " to smell.";
}

std::string GameHandler::handle_taste(Player &player,
                                      const Command &command) const {
    if (command.target.empty()) {
        return player.location()->taste_desc;
    }
    if (command.target == "self") {
        return player.get_description(Verb::taste);
    }
    return player.location()->find_object_info(command);
    return "There's nothing called " + command.target + " to taste.";
}

std::string GameHandler::handle_touch(Player &player,
                                      const Command &command) const {
    if (command.target.empty()) {
        return player.location()->touch_desc;
    }
    if (command.target == "self") {
        return player.get_description(Verb::touch);
    }
    return player.location()->find_object_info(command);
    return "There's nothing called " + command.target + " to touch.";
}

std::string GameHandler::handle_hearing(Player &player,
                                        const Command &command) const {
    if (command.target.empty()) {
        return player.location()->sound_desc;
    }
    if (command.target == "self") {
        return player.get_description(Verb::hearing);
    }
    return player.location()->find_object_info(command);
    return "There's nothing called " + command.target + " to listen to.";
}

std::string GameHandler::handle_get(GameState &game_state,
                                    const Command &command) {
    std::println("-");
    std::string handle_response{"I'm not able to get that."};
    for (const auto &item : game_state.player.location()->room_items) {
        std::string alias_check{item->get_alias(command.target)};

        if (alias_check != "none" && alias_check == item->get_type()) {
            std::println("ActionVerb::get: {}", item->get_name());
            int item_num = game_state.player.location()->find_object_get(
                command.verb, alias_check);

            if (item_num == -1) {
                break;
            }

            std::println("item_num: {}", item_num);
            auto picked_up_item = game_state.world_items.at(item_num).get();
            handle_response =
                "I just picked up a " + picked_up_item->item_name + ".";
            game_state.player.get_object(picked_up_item);
            handle_response = "I just picked up a " + command.target + ".";
            break;
        }
    }
    return handle_response;
}

std::string GameHandler::handle_drop(GameState &game_state,
                                     const std::string &target) {
    int item_dropped{game_state.player.drop_object(target)};
    if (item_dropped != -1) {
        game_state.player.location()->find_object_drop(
            game_state.world_items.at(item_dropped).get());

        return "The " + target + " dropped.";
    }
    return "No " + target + " to be dropped.";
}

std::string GameHandler::handle_use(Player &player, const Command &command) {
    if (command.target.empty()) {
        return "Use what exactly?";
    }
    if (command.extended.empty()) {
        for (auto &item : player.inventory) {
            if (item->get_type() == command.target) {
                return item->components.get_comp_name(CompType::usage);
            }
        }
        for (auto &item : player.location()->room_items) {
            if (item->get_type() == command.target) {
                return "I " + command.verb + " that " + command.target + ".";
            }
        }
        return "There's no way to use that right now.";
    }
    if (!command.extended.empty()) {
        if (command.extended.size() > 1) {
            return "I use the " + command.target + " " +
                   command.extended.at(0) + " the " + command.extended.at(1);
        } else {
            return "I use the " + command.target + " " + command.extended.at(0);
        }
    }

    return "Not yet..";
}

std::string GameHandler::handle_move(Player &player,
                                     std::vector<std::shared_ptr<Room>> &rooms,
                                     const Command &command) {
    if (player.location()->exits.contains(command.target)) {
        player.location() =
            rooms.at(player.location()->exits.at(command.target));
    }
    return "I'm moving.. not right now atleast.";
}

std::string GameHandler::handle_error(Player &player,
                                      const Command &command) const {
    return "That doesn't work..";
}

std::string GameHandler::handle_inventory(ui::GameText &game_text,
                                          const Player &player) const {
    game_text.add_event(ui::EventType::System, "___] Inventory [____");
    game_text.add_event(ui::EventType::System, "");
    if (player.inventory.empty()) {
        game_text.add_event(ui::EventType::System, "*  empty");
    } else {
        for (auto &item : player.inventory) {
            game_text.add_event(ui::EventType::System,
                                "*   " + item->get_name() + " - " +
                                    item->get_type());
        }
    }
    game_text.add_event(ui::EventType::System, "");
    game_text.add_event(ui::EventType::System, "-------------------");

    return "";
}
