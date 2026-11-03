#ifndef GAME_EVENT_HPP
#define GAME_EVENT_HPP

#include "sense.hpp"
#include <string>

struct SensoryEvent {
    Sense sense;
    std::string text;
};

class Command {
  public:
    ~Command() {}
    std::string verb;
    std::string target;
    std::vector<std::string> extended;
    void clear() {
        verb.clear();
        target.clear();
        extended.clear();
    }
};

enum class Verb {
    examine,
    look,
    smell,
    taste,
    touch,
    hearing,
    get,
    drop,
    use,
    move
};

enum class Utils { menu, inventory };

#endif
