#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>

#include "../ui/ui_port.hpp"

#include "../app/app_state.hpp"
#include "game_handler.hpp"

class Game {
  public:
    Game() {}
    Game(size_t sc_width, size_t sc_height)
        : screen_width(sc_width), screen_height(sc_height) {}
    ~Game() {}

    int screen_width;
    int screen_height;
    const int FPS = 60;
    const int delta_time = GetFrameTime();

    ui::GameText game_text;

    void init(AppState &app_state);
    void menu(Mode &mode);
    void run(GameState &game_state);
    void update(GameState &game_state);

  private:
    void calculate_light(Player &player);
    void parse_input(const ui::EventEntry &event);
    void render(Player &player, const std::string &text);
    void quit();

    // GameClock clock;
    GameHandler game_handler;

    Command command_;
    std::string input_text;
};

#endif
