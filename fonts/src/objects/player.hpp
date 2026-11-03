#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include <string>
#include <vector>

#include "../game/game_event.hpp"
#include "../objects/object.hpp"

class Room;

struct Position {
    int elevation = 0;
};

class Player {
  public:
    int id_num = 0;
    std::string name = "Brune";
    Position pos;

    std::vector<Object *> inventory;

    std::shared_ptr<Room> location() const;

    void init(GameState &game_state);
    void set_location(std::shared_ptr<Room> room);
    std::string get_description(Verb verb_command);

    void get_object(Object *item);
    int drop_object(const std::string &dropped_item);

  private:
    std::shared_ptr<Room> location_;
    std::string examine =
        "You haven'thought this deep about anything before in my life.";
    std::string description = "I'm not sure what's goin on.";
    std::string smell = "You stink. Wow..";
    std::string taste = "Salty..";
    std::string touch = "It feels like you haven't bathed in years.";
    std::string sound = "You can hear your own heart beat.";
};

#endif
