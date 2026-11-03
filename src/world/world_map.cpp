#include "world_map.hpp"
#include "../app/app_state.hpp"
#include "../world/room.hpp"

void WorldMap::load_map(GameState &game_state) {
    std::vector<std::shared_ptr<Room>> map_of_rooms;

    auto room_0 = std::make_shared<Room>();
    room_0->room_id = 0;
    room_0->room_name = "Cell";
    room_0->light_env.light = 0;
    room_0->generic_desc = {
        "The darkness conceals the room entirely. Water is dripping somewhere "
        "nearby, its quiet tapping interrupted by the occasional drop striking "
        "stone. The air is cold and damp. Beneath my feet, the floor feels "
        "uneven, and the surrounding walls remain beyond the reach of my "
        "hands.",
        "The darkness reveals little. I can make out only the cramped stone "
        "around me, and somewhere above, a faint pale light filters through a "
        "narrow gap in the darkness.The drip continues. Damp, cold stone "
        "presses "
        "against my back and beneath me. The stale scent of old mold hangs "
        "faintly in the air."};
    room_0->examine_desc = {
        "It's too dark to examine anything right now.",
        "You run your eyes over what little you can see. The walls are "
        "rough-cut "
        "stone, damp with age, their surfaces uneven beneath your hands. The "
        "floor is little more than the same cold stone you've been resting "
        "against. There is no furniture, no obvious fixture, and no visible "
        "way "
        "out at ground level. Above you, the pale light comes through a solid "
        "barrier set into the stone."};
    room_0->look_desc = {
        "I am completely incapable. It's way too dark.",
        "You strain to see through the darkness. The stone walls are close "
        "around you, rough and uneven, but their edges quickly disapear into "
        "blackness. Above, a faint pale light filters through a narrow gap. "
        "You "
        "still cannot make out what lies beyond it. There is nothing else you "
        "can clearly see."};
    room_0->smell_desc =
        "There is the smell of a very old mold. It is both slightly repelling, "
        "while being just as awkwardly entrancing.";
    room_0->sound_desc =
        "You hear faint echoes of.. something, from above you. Muffled.";
    room_0->taste_desc = "You can taste the acridness in the air.";
    room_0->touch_desc = "The stones of this cell are rough, cold, and damp.";
    room_0->near_room_info = "This room is utter darkness.";

    room_0->room_items.push_back(game_state.world_items.at(0).get());
    room_0->room_items.push_back(game_state.world_items.at(1).get());
    room_0->room_items.push_back(game_state.world_items.at(2).get());

    game_state.rooms.clear();
    game_state.rooms.push_back(std::move(room_0));
}
