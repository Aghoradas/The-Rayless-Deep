#ifndef UI_PORT_HPP
#define UI_PORT_HPP
#include <deque>
#include <raylib.h>
#include <string>
#include <vector>

#include "../app/app_state.hpp"
#include "keyboard_input.hpp"

#include "../objects/player.hpp"

class Room;

namespace ui {

struct GameBox {
    int x_pos = 10;
    int y_pos = 10;
    int width = 0;
    int height = 0;
};

struct ComBox {
    int x_pos = 10;
    int y_pos = 0;
    int width = 0;
    int height = 0;
};

enum class EventType { Command, System, Error };

struct EventEntry {
    EventType type;
    std::string text;
};

class GameText {
  public:
    keyboard::Data keyboard_input;

    bool init(int game_width, int game_box_height);
    ~GameText() {
        UnloadFont(game_font);
        UnloadFont(com_font);
        UnloadFont(player_font);
    }

    void add_event(const EventType type, const std::string event);
    EventEntry get_input(std::string &text);

    void menu_input(Mode &mode);
    void draw_menu(size_t screen_width, size_t screen_height);
    void draw_game(size_t screen_width, size_t screen_height,
                   const std::string &text, const Player &player);

    void scroll_up();
    void scroll_down();

  private:
    char cursor[3] = "_";

    Font game_font;
    int game_font_size = 18;
    Font com_font;
    int com_font_size = 35;
    Font player_font;

    std::string game_font_location = "";
    std::string com_font_location = "";
    std::string player_font_location = "";

    int wrap_edge = 250;
    int text_space = 1;
    int text_height = 28.0f;

    Texture2D menu_bg;
    Texture2D menu_logo;

    std::string ui_frame_loc;
    Texture2D ui_frame;

    GameBox game_box;
    Rectangle game_rec_inner;

    float content_y = 0.0f;
    float content_height = 0.0f;

    float scroll_offset = 0.0f;
    float visible_height = 400.0f;

    float command_screen_div = 4;
    float game_rec_division = 2.5;

    ComBox com_box;
    int edge_buffer = 10;
    int com_edge_buffer = 20;

    std::string event_text;
    std::deque<EventEntry> game_events;

    std::vector<std::string> word_wrap(const std::string &text, int max_width);
    void produce_prompt(const Player &player, const std::string text) const;
};

} // namespace ui

#endif
