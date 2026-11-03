#ifndef LIGHT_COMPONENT_HPP
#define LIGHT_COMPONENT_HPP

#include "comp_part.hpp"
#include <algorithm>
#include <string_view>
#include <vector>

class LightEnv {
    // light can be 0(pitch black) - 5(bright light)
  public:
    int light = 0;

    void calculate_room_light(const std::vector<float> &light_levels) {
        float remaing_darkness = 1.0f;
        for (float level : light_levels) {
            level = std::clamp(level, 0.0f, 3.0f);
            remaing_darkness *= 1.0f - (level / 3.0f);
        }
        light = 3.0f * (1.0f - remaing_darkness);
    }
};

class LightSource : public Component {

  public:
    LightSource() {}
    LightSource(bool emit, float lvl) : is_emitting(emit), level(lvl) {}

    int get_lvl() { return level; }
    std::string get_name() override { return comp_name; }

  private:
    std::string comp_name = "LightComponent";
    bool is_emitting = false;
    float level = 0.0f;
};

#endif
