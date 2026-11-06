#ifndef LOOSE_STONE_HPP
#define LOOSE_STONE_HPP

#include "../objects/object.hpp"
#include "objects/components/comp_system.hpp"
#include <string>

class LooseStone : public Object {

  private:
    ObjectLocation location = ObjectLocation::Room;
    std::string name = "loose_stone";
    std::string type = "stone";
    std::vector<std::string> aliases = {"stone", "rock"};
    std::vector<std::string> examine = {
        "It so dark in here. I can't even see the stone, let alone examine it.",
        "A stone rests near the trickling leak, partially "
        "concealed among the damp rock.",
        ""};
    std::vector<std::string> look = {
        "I can't even see the stone, its so dark in here.",
        "The stone sits near the leak where the surrounding "
        "stone has been softened by years of dripping water."};
    std::string touch =
        "The stone is cold, damp, and rough. It shifts slightly "
        "when you press it.";
    std::string sound =
        "Water trickles nearby, occasionally striking the stone "
        "with a soft, hollow sound.";
    std::string smell = "It has a definite earthy and moldy smell.";
    std::string taste = "It has a robustly bland taste, with a slightly "
                        "fermented taste of rotted fruit.";
    std::string description = "nothing realy";
    bool visible{false};
    bool discovered{false};
    bool takeable{true};

  public:
    ObjectId item_id = 1;
    LooseStone() {}
    CompSystem components;
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
    bool has_component(CompType type) override {
        if (components.has_component(type)) {
            return true;
        }
        return false;
    }
    Component *get_comp(CompType type) override {
        return components.get_component(type);
    }
    const std::vector<std::string> get_aliases() override { return aliases; }
    const std::string &examine_info(int light) override {
        return examine.at(light);
    }
    const std::string &sight_info(int light) override { return look.at(light); }
    const std::string &touch_info() override { return touch; }
    const std::string &sound_info() override { return sound; }
    const std::string &smell_info() override { return smell; }
    const std::string &taste_info() override { return taste; }
};

#endif
