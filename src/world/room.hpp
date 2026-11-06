#ifndef ROOM_HPP
#define ROOM_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../game/game_event.hpp"
#include "../objects/object.hpp"
#include "light_env.hpp"

class RoomDoor;
class Player;
class GameState;

class Room {

  public:
    int room_id = 0;
    std::string room_name = "Cell";
    std::vector<std::string> generic_desc = {
        "I can't see anything.",
        "The darkness reveals little. I can make out only the cramped stone "
        "around me, and somewhere above, a faint pale light filters through a "
        "narrow gap in the darkness. The drip continues. Damp, cold stone "
        "presses against my back and beneath me. The stale scent of old mold "
        "hangs faintly in the air."};
    std::vector<std::string> examine_desc = {
        "It's too dark to examine anything right now.",
        "I run my eyes over what little I can see. The walls are "
        "rough-cut "
        "stone, damp with age, their surfaces uneven beneath my hands. The "
        "floor is little more than the same cold stone that I've been resting "
        "against. There is no furniture, no obvious fixture, and no visible "
        "way "
        "out at ground level. Above me, the pale light comes through a solid "
        "barrier set into the stone."};
    std::vector<std::string> look_desc = {
        "I am completely incapable. It's way too dark.",
        "You strain to see through the darkness. The stone walls are close "
        "around you, rough and uneven, but their edges quickly disapear into "
        "blackness. Above, a faint pale light filters through a narrow gap. "
        "You "
        "still cannot make out what lies beyond it. There is nothing else you "
        "can clearly see."};
    std::string smell_desc =
        "There is the smell of a very old mold. It is both slightly repelling, "
        "while being just as awkwardly entrancing.";
    std::string sound_desc =
        "You hear faint echoes of.. something, from above you. Muffled.";
    std::string taste_desc = "You can taste the acridness in the air.";
    std::string touch_desc =
        "The stones of this cell are rough, cold, and damp.";

    std::string near_room_info = "This room is utter darkness.";
    LightEnv light_env{};
    std::unordered_map<std::string, std::shared_ptr<RoomDoor>> doors;
    std::unordered_map<std::string, int> exits;
    std::vector<Object *> room_items;

    bool init(GameState &state);
    void set_exits(std::string direction, int next_room);
    void set_room_items(Object *item) { room_items.emplace_back(item); }

    std::string get_generic();
    std::string get_examine();
    std::string get_look();

    bool is_alias(const Command &command, Object &item);
    std::string find_object_info(const Command &command);
    int find_object_get(const std::string &verb,
                        const std::string &alias_check);
    void find_object_drop(Object *dropped_item);
};

#endif
