#ifndef DOOR_HPP
#define DOOR_HPP

#include "object.hpp"
#include "objects/components/comp_system.hpp"
#include "objects/components/light_component.hpp"

class Door : public Object {
  public:
    // virtual bool open();
    // virtual bool close();
    // virtual bool is_locked();
};

class RoomDoor : public Door {
  private:
    bool closed = true;
    bool locked = false;

  public:
    RoomDoor() {}
    ObjectLocation location = ObjectLocation::Room;
    std::string name = "cell_door";
    std::string type = "door";

    std::vector<std::string> aliases = {"door", "light"};
    std::pair<int, int> connected_rooms;
    std::string description =
        "A round, heavy wooden door is set into the stone above you. A faint "
        "sliver of light seeps from beyond it.";
    std::vector<std::string> examine = {
        "Its way too dark to examine that.",
        "The door is thick and round, and made of dark, weathered wood, "
        "reinforced with crude iron bands. The wood is swollen from years of "
        "dampness, and the iron is mottled with rust. A faint line of pale "
        "light "
        "seeps from its edges. You can see no handle or latch from this side."};
    std::vector<std::string> look = {
        "All I can see of it is a sliver of light. And nothing else.",
        "The door is thick and round, made of a dark wood, "
        "swollen from dampness and reinforced with crude iron "
        "bands. A thin line of pale light escapes from its edges"};
    std::string touch =
        "The wood is cold and rough beneath your fingers. Moisture has "
        "softened "
        "parts of the grain, while the iron feels bitterly cold.";
    std::string sound = "When you press against it, the door gives a low "
                        "groan. Somewhere within "
                        "it, old hinges shift with a faint metallic creak.";
    std::string smell = "The wood carries the smell of damp rot and old iron.";
    std::string taste = "Uh.. you think about it, but decide not to.";

  public:
    ObjectId item_id = 0;
    CompSystem components;

    bool visible{false};
    bool discovered{false};
    bool takeable{false};

    std::vector<Interaction> interractions;

    const ObjectId get_id() override { return item_id; }
    const std::string &get_name() override { return name; }
    const std::string &get_type() override { return type; }
    const bool &is_takeable() override { return takeable; }
    const std::string get_alias(std::string target) override {
        for (auto &alias : aliases) {
            if (target == alias) {
                return alias;
            }
        }
        std::string none = "none";
        return none;
    }
    const std::vector<std::string> get_aliases() override { return aliases; }

    const int get_light() override {
        Component *component_light = components.get_component(CompType::light);
        if (auto door_light = dynamic_cast<LightSource *>(component_light)) {

            return door_light->get_lvl();
        }
        return 0;
    }

    const std::string &examine_info(int light) override {
        return examine.at(light);
    }
    const std::string &sight_info(int light) override { return look.at(light); }
    const std::string &touch_info() override { return touch; }
    const std::string &sound_info() override { return sound; }
    const std::string &smell_info() override { return smell; }
    const std::string &taste_info() override { return taste; }
    bool is_closed() { return closed; }
    bool is_locked() { return locked; }
    void open() {
        if (closed && locked == false) {
            closed = false;
        }
    }
    void close() {
        if (!closed) {
            closed = true;
        }
    }
    void lock_door() {}
    void unlock_door() {}
};

#endif
