#pragma once

#include <string>
#include <map>
#include <windows.h>

class RumbleWriter
{
    private:

        // A map for store the virtual keycodes for every char
        static const std::map<const char, const uint32_t> virtual_keycodes;

        // This structure will be used to create the keyboard input event.
        INPUT input;

    public:
        RumbleWriter();

        void speech_to_keyboard_input(std::string);
};