#ifndef COMP_PART_HPP
#define COMP_PART_HPP

class GameState;
class Object;

class Component {
  public:
    virtual ~Component() {}
    virtual std::string get_name() { return " "; }
};

#endif
