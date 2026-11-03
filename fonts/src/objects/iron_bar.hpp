#ifndef IRON_BAR_HPP
#define IRON_BAR_HPP

#include "../objects/object.hpp"
#include "objects/components/comp_system.hpp"

class IronBar : public Object {
  public:
    ObjectLocation location = ObjectLocation::Room;

    std::string name = "iron_bar";
    std::string type = "bar";
    std::vector<std::string> aliases = {"bar", "iron"};
    std::vector<std::string> examine = {
        "I can't examine it in this darkness.",
        "Its just an iron bar, heavily weathered and mottled with rust."};
    std::vector<std::string> look = {
        "Its too dark to look at anything.",
        "Something land and narrow lies within reach, though the "
        "darkness makes its shape difficult to discern."};
    std::string touch = "The iron is cold, hard, wet, and rough with rust.";
    std::string sound =
        "The bar gives a dull metallic sound when struck against the stone.";
    std::string smell = "You smell nothing but rusted iron.";
    std::string taste = "Uh.. you think about it, but decide not to.";

    std::string description = "nothing realy";

    bool visible{false};
    bool discovered{false};
    bool takeable{true};

  public:
    ObjectId item_id = 2;
    IronBar() {}
    CompSystem components;
    std::vector<Interaction> interractions;

    const ObjectId get_id() override { return item_id; }
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

    const int get_light() override { return light_source.get_lvl(); }

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
