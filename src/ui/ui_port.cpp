#include "ui_port.hpp"
#include "../app/app_state.hpp"
#include "../objects/player.hpp"
#include "../world/room.hpp"
#include <iostream>
#include <raylib.h>
#include <sstream>

bool ui::GameText::init(int screen_width, int screen_height) {
    std::string menu_bg_file = "../ui_assets/menu_bg.png";
    Image menu_bg_image = LoadImage(menu_bg_file.c_str());
    menu_bg = LoadTextureFromImage(menu_bg_image);
    UnloadImage(menu_bg_image);
    menu_bg.width = screen_width;
    menu_bg.height = screen_height;

    std::string menu_logo_file = "../ui_assets/menu_logo.png";
    Image menu_logo_image = LoadImage(menu_logo_file.c_str());
    menu_logo = LoadTextureFromImage(menu_logo_image);
    UnloadImage(menu_logo_image);

    game_box.x_pos = 5 * edge_buffer;
    game_box.y_pos = 11 * edge_buffer;
    game_box.width = screen_width - (edge_buffer * 10);
    game_box.height = screen_height - screen_height / game_rec_division;

    game_rec_inner = {(float)game_box.x_pos + 125, (float)game_box.y_pos + 30,
                      (float)game_box.width - 250, (float)game_box.height};

    com_box.x_pos = edge_buffer * 12;
    com_box.y_pos = screen_height - screen_height / command_screen_div;
    com_box.width = screen_width - com_box.x_pos;
    com_box.height = screen_height / command_screen_div + com_edge_buffer;

    ui_frame_loc = "../ui_assets/rayless_deep_frame.png";
    Image ui_frame_image = LoadImage(ui_frame_loc.c_str());
    ui_frame = LoadTextureFromImage(ui_frame_image);
    UnloadImage(ui_frame_image);
    ui_frame.width = screen_width;
    ui_frame.height = screen_height;

    player_font_location = "../fonts/ProggyCleanM-R.ttf";

    int time_out_font = 0;
    do {
        time_out_font += 1;
        player_font = LoadFont(player_font_location.c_str());
        if (time_out_font > 3) {
            game_font = GetFontDefault();
            std::cerr << "player_font error with LoadFont() at \""
                      << game_font_location << "\".\n";
            return false;
        }
    } while (!IsFontValid(player_font));

    time_out_font = 0;
    do {
        time_out_font += 1;
        game_font_location = "../fonts/BigBlueTerm.ttf";
        game_font = LoadFont(game_font_location.c_str());
        if (time_out_font > 3) {
            game_font = GetFontDefault();
            std::cerr << "game_font error with LoadFont() at \""
                      << game_font_location << "\".\n";
            return false;
        }
    } while (!IsFontValid(game_font));

    time_out_font = 0;
    do {
        time_out_font += 1;
        com_font_location = "../fonts/VT323-Regular.ttf";
        com_font = LoadFont(com_font_location.c_str());
        if (time_out_font > 3) {
            com_font = GetFontDefault();
            std::cerr << "game_font error with LoadFont() at \""
                      << com_font_location << "\".\n";
        }
    } while (!IsFontValid(com_font));

    return true;
}

// add_event
void ui::GameText::add_event(const EventType type, const std::string event) {
    if (type == EventType::System) {

        std::vector<std::string> lines_to_print =
            word_wrap(event.c_str(), game_box.width - wrap_edge);
        for (std::string &line : lines_to_print) {
            game_events.push_back({type, line});
            content_height += text_height;
        }

    } else {

        game_events.push_back({EventType::System, ""});
        content_height += text_height;

        game_events.push_back({type, event});
        content_height += text_height;
    }
    if (content_height >= game_rec_inner.height) {
        scroll_offset = game_rec_inner.height - content_height;
    }
}

// get_input
ui::EventEntry ui::GameText::get_input(std::string &text) {
    // Prompt and so on here
    bool is_event = keyboard_input.active(text, event_text);
    if (is_event && event_text.empty()) {
        add_event(EventType::Command, "nothing said");
        add_event(EventType::System,
                  "I can only wait for death in a place like this.");
        return {EventType::Error, ""};
    }
    if (is_event) {
        add_event(EventType::Command, event_text);
        event_text.clear();
        return game_events.back();
    }
    return {EventType::Error, "nothing"};
}

// menu_input
void ui::GameText::menu_input(Mode &mode) {
    keyboard::Data key_input;
    std::string menu_input;
    std::string text;
    if (IsKeyPressed(KEY_ENTER)) {
        mode = Mode::GamePlay;
    }
}

void ui::GameText::draw_menu(size_t screen_width, size_t screen_height) {
    Rectangle full_screen = {0, 0, (float)screen_width, (float)screen_height};
    DrawTextureRec(menu_bg, full_screen, {0, 0}, WHITE);
    std::string press_ent = "[Press Enter]";
    Vector2 text_measure =
        MeasureTextEx(game_font, press_ent.c_str(), game_font_size, 4);
    DrawTextEx(game_font, "[Press Enter]",
               {(float)screen_width / 2 - text_measure.x / 2, 700},
               game_font_size, 4, ORANGE);
}

void ui::GameText::draw_game(size_t screen_width, size_t screen_height,
                             const std::string &text, const Player &player) {

    Rectangle full_screen = {0, 0, (float)screen_width, (float)screen_height};
    DrawTextureRec(ui_frame, full_screen, {0, 0}, WHITE);

    // SCISSOR MODE BEGINS
    BeginScissorMode(game_rec_inner.x, game_rec_inner.y, game_rec_inner.width,
                     game_rec_inner.height);

    // Draw event list
    float draw_y = game_rec_inner.y + scroll_offset;
    Vector2 text_position = {game_rec_inner.x, draw_y};

    for (const auto &current_line : game_events) {
        if (current_line.type == EventType::System) {
            DrawTextEx(game_font, current_line.text.c_str(), text_position,
                       game_font_size, 4, ORANGE);
            text_position.y += text_height;
        } else if (current_line.type == EventType::Command) {
            DrawTextEx(player_font, current_line.text.c_str(), text_position,
                       game_font_size, 4, WHITE);
            text_position.y += text_height;
        }
    }
    EndScissorMode();
    // SCISSOR ENDS

    // Draw current command input
    produce_prompt(player, text);
}

std::vector<std::string> ui::GameText::word_wrap(const std::string &text,
                                                 int max_width) {
    std::vector<std::string> lines;
    std::istringstream words(text);

    std::string word;
    std::string line = "    ";

    float message_height = 0.0f;
    Vector2 text_size = {0, 0};

    while (words >> word) {
        std::string test_line = line.empty() ? word : line + " " + word;

        text_size =
            MeasureTextEx(game_font, test_line.c_str(), game_font_size, 4);

        if (text_size.x <= max_width) {
            line = test_line;
        } else {
            lines.emplace_back(line);
            line = word;
        }
    }

    if (!line.empty()) {
        lines.emplace_back(line);
    }

    return lines;
}

void ui::GameText::produce_prompt(const Player &player,
                                  const std::string text) const {
    // Command Prompt
    std::string prompt = " [Location: ";
    Vector2 com_position = {(float)com_box.x_pos + (edge_buffer),
                            (float)com_box.y_pos + (float)com_box.height / 2};
    DrawTextEx(com_font, prompt.c_str(), com_position, com_font_size,
               text_space, DARKBROWN);

    Vector2 cursor_pos =
        MeasureTextEx(com_font, prompt.c_str(), com_font_size, text_space);
    prompt = player.location()->room_name;
    com_position.x += cursor_pos.x;
    DrawTextEx(com_font, prompt.c_str(), com_position, com_font_size,
               text_space, DARKGRAY);

    cursor_pos =
        MeasureTextEx(com_font, prompt.c_str(), com_font_size, text_space);
    prompt = "] ";
    com_position.x += cursor_pos.x;
    DrawTextEx(com_font, prompt.c_str(), com_position, com_font_size,
               text_space, DARKBROWN);

    cursor_pos =
        MeasureTextEx(com_font, prompt.c_str(), com_font_size, text_space);
    prompt = ":";
    com_position.x += cursor_pos.x;
    DrawTextEx(com_font, prompt.c_str(), com_position, com_font_size,
               text_space, ORANGE);

    cursor_pos =
        MeasureTextEx(com_font, prompt.c_str(), com_font_size, text_space);
    prompt = "> ";
    com_position.x += cursor_pos.x;
    DrawTextEx(com_font, prompt.c_str(), com_position, com_font_size,
               text_space, RED);

    // Currently Typed Text
    cursor_pos =
        MeasureTextEx(com_font, prompt.c_str(), com_font_size, text_space);
    cursor_pos.x += com_position.x;
    cursor_pos.y = com_position.y;
    DrawTextEx(com_font, text.c_str(), cursor_pos, com_font_size, text_space,
               LIGHTGRAY);

    // Cursor
    Vector2 cursor_mov =
        MeasureTextEx(com_font, text.c_str(), com_font_size, text_space);
    cursor_pos.x += cursor_mov.x;
    cursor_pos.y = com_position.y;
    DrawRectangle((cursor_pos.x + text_space * 2), cursor_pos.y, 15,
                  com_font_size, DARKGRAY);

    return;
}
