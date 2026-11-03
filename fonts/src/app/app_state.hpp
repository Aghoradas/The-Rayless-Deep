#ifndef APP_STATE_HPP
#define APP_STATE_HPP

#include <memory>
#include <raylib.h>
#include <unordered_map>

#include "../objects/object.hpp"
#include "../objects/player.hpp"
#include "../world/room.hpp"

class GameState {
  public:
    Player player{};
    std::vector<std::unique_ptr<Object>> world_items{};
    std::vector<std::shared_ptr<Room>> rooms{};
    std::unordered_map<std::string, Music> music_list{};
    // std::unordered_map<int, std::string> room_aliases;
    // GameTime time;
    ~GameState() {
        for (auto item : music_list) {
            UnloadMusicStream(item.second);
        }
    }
};

enum class Mode { Menu, Creation, GamePlay, EndGame };

struct AppState {
    size_t screen_width{};
    size_t screen_height{};

    Mode mode = Mode::Menu;
    GameState game_state{};
};

#endif
