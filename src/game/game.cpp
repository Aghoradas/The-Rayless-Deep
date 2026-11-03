#include "game.hpp"
#include <memory>
#include <raylib.h>
#include <sstream>
#include <string>

#include "../app/app_state.hpp"
#include "../objects/components/comp_part.hpp"
#include "../objects/object.hpp"
#include "../objects/player.hpp"
#include "../world/map_loader.hpp"
#include "../world/world_map.hpp"
#include "game_event.hpp"
#include "objects/components/comp_system.hpp"
#include "ui/ui_port.hpp"

void Game::init(AppState &app_state) {

    game_text.init(screen_width, screen_height);

    SetTargetFPS(FPS);
    game_text.add_event(ui::EventType::System, "An unbearable darkness..");
    game_text.add_event(ui::EventType::System,
                        "Drip drip..   its the first sound I'm hearing.");
    game_text.add_event(
        ui::EventType::System,
        "The echoes of yesterday resurface, and what happened.");
    game_text.add_event(ui::EventType::System, "How many days has it been?");
    game_text.add_event(ui::EventType::System, "I couldn't say.");
    game_text.add_event(
        ui::EventType::System,
        "Still no idea where I am, but I know what brought me here.");
    game_text.add_event(ui::EventType::System,
                        "Dripping water is my eternity.");
    game_text.add_event(
        ui::EventType::System,
        "The lack of visible surroundings creep back into focus.");
    game_text.add_event(ui::EventType::System,
                        "Once again, my eyes adjust to this dark place.");

    WorldMap world_map;
    world_map.load_items(app_state.game_state);
    std::cout << "Item test: "
              << app_state.game_state.world_items.at(0)->get_name()
              << std::endl;
    world_map.load_map(app_state.game_state);
    std::cout << "GameState room_items test: "
              << app_state.game_state.rooms.at(0)->room_items.at(0)->get_name()
              << std::endl;

    //// LOADING OBJECTS AND ROOMS FROM JSON /////////////////
    // --still under construction----------------------------
    MapLoader map_loader;
    map_loader.init_world(app_state.game_state);
    //-------------------------------------------------------

    app_state.game_state.player.init(app_state.game_state);
    game_text.add_event(ui::EventType::System, "");
    game_text.add_event(ui::EventType::System,
                        app_state.game_state.player.location()->get_generic());
    std::cout << "\nGame init() complete.." << std::endl;
}

void Game::menu(Mode &mode) {
    BeginDrawing();
    ClearBackground(BLACK);

    game_text.menu_input(mode);
    game_text.draw_menu(screen_width, screen_height);

    EndDrawing();
}

// Main Game Loop
void Game::run(GameState &game_state) {
    std::cout << "game running..\n";

    while (!WindowShouldClose()) {
        UpdateMusicStream(game_state.music_list.at("cell_room"));
        BeginDrawing();
        ClearBackground(BLACK);

        ui::EventEntry command_text = game_text.get_input(input_text);

        if (command_text.type != ui::EventType::Error) {
            parse_input(command_text);
            std::string game_response =
                game_handler.command_handler(game_state, game_text, command_);
            command_.clear();
            game_text.add_event(ui::EventType::System, game_response);
        }

        update(game_state);
        render(game_state.player, input_text);
        EndDrawing();
    }
    quit();
}

void Game::update(GameState &game_state) {
    std::vector<float> light_levels;
    for (const auto &item : game_state.player.location()->room_items) {
        if (item->components.has_component(CompType::light)) {
            light_levels.emplace_back(item->get_light());
        }
    }
    for (const auto &item : game_state.player.inventory) {
        if (item->components.has_component(CompType::light)) {
            light_levels.emplace_back(item->get_light());
        }
    }

    game_state.player.location()->light_env.calculate_room_light(light_levels);
}

void Game::parse_input(const ui::EventEntry &event) {
    std::string new_command = event.text;
    if (event.text.empty()) {
        return;
    }

    for (auto &letter : new_command) {
        letter = std::tolower(letter);
    }

    std::istringstream ss(new_command);

    ss >> command_.verb;
    ss >> command_.target;
    std::string word{};
    while (ss >> word) {
        command_.extended.emplace_back(word);
    }
}

void Game::render(Player &player, const std::string &text) {
    std::string player_prompt = " || 100hp || 12xp:>> ";
    game_text.draw_game(screen_width, screen_height, text, player);
}

void Game::quit() {}
