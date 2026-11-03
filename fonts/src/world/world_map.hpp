#ifndef WORLD_MAP_HPP
#define WORLD_MAP_HPP

#include <memory>
#include <vector>

class GameState;

class Room;

class WorldMap {
  public:
    void load_items(GameState &game_state);
    void load_map(GameState &game_state);
    Room *access_room(int room_id) { return world_rooms.at(room_id).get(); }

  private:
    std::vector<std::shared_ptr<Room>> world_rooms;

    void load_map_json();
};

#endif
