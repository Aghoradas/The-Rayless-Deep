#include <memory>
#include <vector>

#include "../app/app_state.hpp"
#include "../objects/components/comp_part.hpp"
#include "../objects/components/comp_system.hpp"
#include "map_loader.hpp"
#include "objects/components/usage_component.hpp"

#include "../objects/door.hpp"
#include "../objects/iron_bar.hpp"
#include "../objects/loose_stone.hpp"
#include "../objects/object.hpp"

void MapLoader::load_items(GameState &game_state) {
    std::vector<std::unique_ptr<Object>> world_items;

    auto cell_door = std::make_unique<RoomDoor>();
    auto light_component = std::make_unique<LightSource>(true, 0.5f);
    cell_door->components.add_component(CompType::light,
                                        std::move(light_component));

    auto loose_stone = std::make_unique<LooseStone>();
    auto use_component = std::make_unique<UsageComponent>("use");
    loose_stone->components.add_component(CompType::usage,
                                          std::move(use_component));

    auto iron_bar = std::make_unique<IronBar>();

    world_items.push_back(std::move(cell_door));
    world_items.push_back(std::move(loose_stone));

    world_items.push_back(std::move(iron_bar));

    std::cout << "If item test below doesn't print, items not loading."
              << std::endl;
    std::cout << "Item test: " << world_items.at(0)->sight_info(0) << std::endl;

    game_state.world_items = std::move(world_items);
}
