#include <map>
#include <iostream>

#include "RumbleWriter.h"

const std::map<const char, const uint32_t> RumbleWriter::virtual_keycodes
{
    // Special keyboard caps
    { ' ', 0X08 }, // BACKSPACE
    { ' ', 0X20 }, // SPACEBAR
    // Common letters
    { 'a', 0X41 }, { 'b', 0X42 }, { 'c', 0X43 }, { 'd', 0X44 }, { 'e', 0X45 }, { 'f', 0X46 },
    { 'g', 0X47 }, { 'h', 0X48 }, { 'i', 0X49 }, { 'j', 0X4A }, { 'k', 0X4B }, { 'l', 0X4C }, 
    { 'm', 0X4D }, { 'n', 0X4E }, { 'o', 0X4F }, { 'p', 0X50 }, { 'q', 0X51 }, { 'r', 0X52 },
    { 's', 0X53 }, { 't', 0X54 }, { 'u', 0X55 }, { 'v', 0X56 }, { 'w', 0X57 }, { 'x', 0X58 },
    { 'y', 0X59 }, { 'z', 0X5A }
};

RumbleWriter::RumbleWriter()
{
    // Setting up a generic keyboard event.
    INPUT kb_input;
    kb_input.type = INPUT_KEYBOARD;
    kb_input.ki.wScan = 0; // hardware scan code for key
    kb_input.ki.time = 0;
    kb_input.ki.dwExtraInfo = 0;

    // Assign it to member variable
    this->input = kb_input;
}

void RumbleWriter::speech_to_keyboard_input(std::string text_from_voice)
{
    std::map<const char, const uint32_t>::const_iterator it;
    uint32_t keystroke;

    for (const char &c : text_from_voice)
    {
        // Map the character with it's correspondent keycode
        it = virtual_keycodes.find( c );

        if (it != virtual_keycodes.end()) 
            keystroke = it->second;
        else
        {
            std::cout << "[WARNING] NOT allowed char -> " << c << std::endl;
        }
            // TODO 
            // Throw an exception indicating that a non-allowed character has been passed into this method

        // Press the key
        this->input.ki.wVk = keystroke; // virtual-key code for the key
        this->input.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &input, sizeof(INPUT));

        // Release the key
        this->input.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
        SendInput(1, &input, sizeof(INPUT));
    }

}