#ifndef GAME_HANDLER_HPP
#define GAME_HANDLER_HPP

#include "../app/app_state.hpp"
#include "../world/room.hpp"
#include "game_event.hpp"
#include "ui/ui_port.hpp"
#include <memory>

class Player;

class GameHandler {
  public:
    ~GameHandler() {}
    std::string command_handler(GameState &game_state, ui::GameText &game_text,
                                Command &command);

  private:
    // Utils Handlers
    std::string handle_menu();
    std::string handle_inventory(ui::GameText &game_text,
                                 const Player &player) const;

    // Verb Handlers
    std::string handle_examine(Player &player, const Command &command) const;
    std::string handle_look(Player &player, const Command &command) const;
    std::string handle_smell(Player &player, const Command &command) const;
    std::string handle_taste(Player &player, const Command &command) const;
    std::string handle_touch(Player &player, const Command &command) const;
    std::string handle_hearing(Player &player, const Command &command) const;

    std::string handle_get(GameState &game_state, const Command &command);
    std::string handle_drop(GameState &game_state, const std::string &target);
    std::string handle_use(Player &player, const Command &command);
    std::string handle_move(Player &player,
                            std::vector<std::shared_ptr<Room>> &rooms,
                            const Command &command);

    std::string handle_error(Player &player, const Command &command) const;
};

#endif
