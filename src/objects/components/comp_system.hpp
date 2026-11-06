#ifndef COMP_SYSTEM_HPP
#define COMP_SYSTEM_HPP

#include "comp_part.hpp"
#include <memory>
#include <print>
#include <unordered_map>

class UsageComponent;
class LightSource;

enum class CompType { light, usage };

class CompSystem {
  private:
    std::unordered_map<CompType, std::unique_ptr<Component>> assembly;

  public:
    std::string get_comp_name(CompType type) {
        return assembly.at(type)->get_name();
    }
    bool has_component(CompType type) {
        if (assembly.contains(type)) {
            return true;
        }
        return false;
    }

    void add_component(CompType type, std::unique_ptr<Component> component) {
        assembly.emplace(type, std::move(component));
    }

    Component *get_component(CompType type) {
        if (type != CompType::light) {
            std::println("*CompType: not light");
        }
        return assembly.at(type).get();
    }
};
#endif
