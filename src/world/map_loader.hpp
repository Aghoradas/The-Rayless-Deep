#ifndef WORLD_LOADER_HPP
#define WORLD_LOADER_HPP

#include "../app/app_state.hpp"

class MapLoader {
  public:
    void load_items(GameState &game_state);
    void init_world(GameState &game_state);
};
#endif
