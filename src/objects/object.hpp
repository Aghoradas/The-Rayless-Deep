#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "components/comp_system.hpp"
#include "components/light_component.hpp"
#include <string>
#include <vector>

class GameState;

enum class Interaction {
    Examine,
    Look,
    Take,
    Open,
    Close,
    Push,
    Pull,
    Use,
    Listen,
    Smell
};

enum class ObjectLocation { Room, Inventory, Contained, Removed };

using ObjectId = int;

class Object {
  private:
  public:
    virtual ~Object() {}
    ObjectId id;
    ObjectLocation loc;
    std::string item_name = "some object";
    std::string item_type = "object";
    std::vector<std::string> item_aliases = {"object"};

    std::vector<std::string> item_sight = {
        "You see nothing", "You see a little", "You see everything."};
    std::string item_description = "nothing realy";
    std::vector<Interaction> interractions;

    LightSource light_source;
    CompSystem components{};

    bool takeable{false};

    virtual const ObjectId get_id() { return id; }
    virtual const std::string &get_name() { return item_name; };
    virtual const std::string &get_type() { return item_type; }
    virtual const bool &is_takeable() { return takeable; }

    virtual const std::string get_alias(std::string target) {
        std::string alias = "object";
        return alias;
    }

    virtual const std::vector<std::string> get_aliases() {
        return item_aliases;
    }
    virtual const int get_light() { return light_source.get_lvl(); }

    virtual const std::string &examine_info(int light) {
        return item_sight.at(light);
    }
    virtual const std::string &sight_info(int light) {
        return item_sight.at(light);
    }
    virtual const std::string &touch_info() { return item_description; }
    virtual const std::string &sound_info() { return item_description; }
    virtual const std::string &smell_info() { return item_description; }
    virtual const std::string &taste_info() { return item_description; }
};

#endif
