#define JSON_HAS_CPP_23
#include "map_loader.hpp"
#include "data/nl_json/nlohmann/json.hpp"

#include <filesystem>
#include <fstream>
#include <memory>
#include <print>
#include <string>
#include <vector>

#include "app/app_state.hpp"
#include "room.hpp"

using Json = nlohmann::json;
std::vector<std::string> accepted_keys = {
    "room_id",        "room_name",  "generic_desc", "examine_desc",
    "smell_desc",     "sound_desc", "taste_desc",   "touch_desc",
    "near_room_info", "exits",      "room_items"};

Json open_file_tojson(const std::filesystem::path &file_path) {
    std::ifstream file(file_path);
    if (!file) {
        std::cerr << "*Error openning WorldLoader file_path" << std::endl;
    }
    Json data;
    file >> data;

    if (!data.is_object()) {
        std::cerr << "*Error streaming json file to data." << std::endl;
    }

    return data;
}

bool check_element(const std::string &key, const Json &element) {
    for (const std::string &check_key : accepted_keys) {
        if (!element.contains(check_key)) {
            std::println(
                "*Error check_element from room_data(room {}): {} missing..",
                key, check_key);
            return false;
        }
    }
    return true;
}

std::shared_ptr<Room> json_to_room(const std::string &key,
                                   const Json &element) {
    auto room = std::make_shared<Room>();

    if (!check_element(key, element)) {
        exit(1);
    }

    std::println("-Json_to_room test: {}", element.at("room_id").get<int>());

    if (element["room_id"].is_number_integer()) {
        room->room_id = element["room_id"].get<int>();
    }
    if (element["room_name"].is_string()) {
        room->room_name = element.at("room_name").get<std::string>();
        std::println("-{}", room->room_name);
    }
    if (element["generic_desc"].is_array()) {
        std::println("-Element: generic_desc");
        room->generic_desc.clear();
        for (const auto &el : element["generic_desc"]) {
            std::println("-For generic_desc &el");
            room->generic_desc.push_back(el.get<std::string>());
        }
    }
    if (element["examine_desc"].is_array()) {
        room->examine_desc.clear();
        for (const auto &el : element["examine_desc"]) {
            room->examine_desc.push_back(el.get<std::string>());
        }
    }
    if (element["look_desc"].is_array()) {
        room->look_desc.clear();
        for (const auto &el : element["look_desc"]) {
            room->look_desc.push_back(el.get<std::string>());
        }
    }
    if (element["smell_desc"].is_string()) {
        room->smell_desc = element["smell_desc"].get<std::string>();
    }
    if (element["sound_desc"].is_string()) {
        room->sound_desc = element["sound_desc"].get<std::string>();
    }
    if (element["taste_desc"].is_string()) {
        room->taste_desc = element["taste_desc"].get<std::string>();
    }
    if (element["touch_desc"].is_string()) {
        room->touch_desc = element["touch_desc"].get<std::string>();
    }
    if (element["near_room_info"].is_string()) {
        room->near_room_info = element["near_room_info"].get<std::string>();
    }
    if (element["exits"].is_array()) {
        std::println("-Exits for {} reached.", room->room_name);
    }
    if (element["room_items"].is_array()) {
        std::println("-Room_items for {} reached.", room->room_name);
    }
    return room;
}

void MapLoader::init_world(GameState &game_state) {
    const std::filesystem::path &file_path = "../src/world/data/room_data.json";
    Json data = open_file_tojson(file_path);
    std::cout << "\nGeneric_desc test: "
              << data["world_map"][0].at("room_name").get<std::string>()
              << std::endl;

    size_t contained_rooms = data["contained_rooms"].get<int>();
    std::println("-Contained_rooms: {}", contained_rooms);
    if (!data["world_map"].is_array()) {
        std::println("*json.at(\"world_map\") is not an object.");
    }

    std::println("-Json world_map test, room_name: {}",
                 data["world_map"][0]["room_name"].get<std::string>());

    std::vector<std::shared_ptr<Room>> world_rooms;
    for (auto &element : data["world_map"].items()) {
        world_rooms.push_back(json_to_room(element.key(), element.value()));
    }
}
