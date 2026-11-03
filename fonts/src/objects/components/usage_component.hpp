#ifndef USAGE_COMPONENT_HPP
#define USAGE_COMPONENT_HPP
#include <stdexcept>
#include <string_view>
#include <unordered_map>

#include "../object.hpp"
#include "comp_part.hpp"

enum class UsageType { Use, Open, Unlock, Ignite, Combine };

class Object;

class UsageComponent : public Component {
  private:
    static constexpr std::optional<UsageType>
    string_to_type(std::string_view alone_use) {
        if (alone_use == "use") {
            return UsageType::Use;
        }
        if (alone_use == "open") {
            return UsageType::Open;
        }
        if (alone_use == "unlock") {
            return UsageType::Unlock;
        }
        if (alone_use == "ignite") {
            return UsageType::Ignite;
        }
        if (alone_use == "combine") {
            return UsageType::Combine;
        }
        return std::nullopt;
    }
    std::unordered_map<Object *, UsageType> interactives{};

    UsageType alone_use_type{};
    std::string comp_name = "UsageComponent";

  public:
    UsageComponent() {}
    UsageComponent(std::string_view alone_use) {
        if (auto type = string_to_type(alone_use)) {
            alone_use_type = *type;
        } else {
            throw std::invalid_argument("*Unknown usage of string_to_type.");
        }
    }

    std::string get_name() override { return comp_name; }
    void add_interactive(Object *interactive, std::string_view &with_use) {
        if (!interactives.contains(interactive)) {
            if (auto type = string_to_type(with_use)) {
                interactives.emplace(interactive, *type);
            } else {
                throw std::invalid_argument(
                    "*Unknown interactive_type of string_to_type.");
            }
        }
    }

    std::string use(Object *owner) {
        switch (alone_use_type) {
            using Use = UsageType;
        case Use::Use: {
            return "I open the " + owner->get_type() + ".";
            break;
        }
        case Use::Open: {
            break;
        }
        case Use::Unlock: {
            break;
        }
        case Use::Ignite: {
            break;
        }
        case Use::Combine: {
            break;
        }
        default: {
            break;
        }
        }
        return "It doesn't seem that this " + owner->get_type() +
               " can be used on its own.";
    };
};
#endif
