#ifndef KEYBOARD_INPUT_HPP
#define KEYBOARD_INPUT_HPP

#include <raylib.h>
#include <string>

namespace keyboard {

class Data {

  public:
    int letters = 0;
    int max_letters = 40;

    bool active(std::string &text, std::string &event_text) {

        int key = 0;
        key = GetCharPressed();
        if (key >= 32 && key <= 125 && letters < max_letters) {
            text += key;
            letters++;
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !text.empty()) {
            text.pop_back();
            letters--;
        }
        if (IsKeyPressed(KEY_ENTER)) {
            event_text = text;
            letters = 0;
            text.clear();
            return true;
        }

        return false;
    }
};

} // namespace keyboard

#endif
