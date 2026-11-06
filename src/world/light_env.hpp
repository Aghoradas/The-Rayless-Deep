#ifndef LIGHT_ENV_HPP
#define LIGHT_ENV_HPP

class LightEnv {
    // light can be 0(pitch black) - 5(bright light)
  public:
    float light = 0;

    void calculate_room_light(const std::vector<float> &light_levels) {
        float remaing_darkness = 1.0f;
        for (float level : light_levels) {
            level = std::clamp(level, 0.0f, 3.0f);
            remaing_darkness *= 1.0f - (level / 3.0f);
        }
        light = 3.0f * (1.0f - remaing_darkness);
    }
};

#endif
