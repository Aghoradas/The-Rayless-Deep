#include <raylib.h>

#include "app/app_state.hpp"
#include "game/game.hpp"

int main() {

    InitWindow(0, 0, "The Rayless Deep");
    int current_monitor{GetCurrentMonitor()};
    int SCREEN_WIDTH{GetMonitorWidth(current_monitor)};
    int SCREEN_HEIGHT{GetMonitorHeight(current_monitor)};
    InitAudioDevice();

    std::cout << "w: " << SCREEN_WIDTH << " h: " << SCREEN_HEIGHT << "\n";

    AppState app_state{};
    app_state.mode = Mode::Menu;
    app_state.screen_width = SCREEN_WIDTH;
    app_state.screen_height = SCREEN_HEIGHT;

    Game game(SCREEN_WIDTH, SCREEN_HEIGHT);
    game.init(app_state);
    // WorldLoader world_loader;
    // world_loader.init_world(app_state);

    // Loading music
    app_state.game_state.music_list["menu"] =
        LoadMusicStream("../src/ui/sounds/deep_theme.mp3");
    app_state.game_state.music_list["menu"].looping = true;
    app_state.game_state.music_list["cell_room"] =
        LoadMusicStream("../src/ui/sounds/cell_room.mp3");
    app_state.game_state.music_list["cell_room"].looping = true;

    PlayMusicStream(app_state.game_state.music_list.at("menu"));
    SetMusicVolume(app_state.game_state.music_list.at("menu"), 5.0f);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        switch (app_state.mode) {
        case Mode::Menu: {
            UpdateMusicStream(app_state.game_state.music_list.at("menu"));
            game.menu(app_state.mode);
            break;
        }
        case Mode::Creation: {
            break;
        }
        case Mode::GamePlay: {
            StopMusicStream(app_state.game_state.music_list.at("menu"));
            PlayMusicStream(app_state.game_state.music_list.at("cell_room"));
            game.run(app_state.game_state);
            break;
        }
        case Mode::EndGame: {
            break;
        }
        }
        if (app_state.mode == Mode::EndGame) {
            break;
        }
    }

    CloseWindow();
}
