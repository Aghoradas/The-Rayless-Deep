#ifndef LIGHT_COMPONENT_HPP
#define LIGHT_COMPONENT_HPP

#include "comp_part.hpp"

class LightSource : public Component {

  public:
    LightSource() {}
    LightSource(bool emit, float lvl) : is_emitting(emit), level(lvl) {}

    float get_lvl() { return level; }
    void set_values(bool emitting, float lvl) {
        is_emitting = emitting;
        level = lvl;
    }
    std::string get_name() override { return comp_name; }

  private:
    std::string comp_name = "LightComponent";
    bool is_emitting = false;
    float level = 0.0f;
};

#endif
