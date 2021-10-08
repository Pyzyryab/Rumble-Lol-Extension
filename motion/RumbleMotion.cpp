#include "RumbleMotion.hpp"


/// <summary>
/// Moves the mouse to a designed (x, y) points and performs a left click action when arrives
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void RumbleMotion::move_mouse_and_left_click(int x, int y)
{
    // Correct the mouse position to make a good click. When the OPENCV API returns a matching point, it returns the upper left
    // most outer point, so a pad it's been aplicated here
    // TODO Aplicate padding in another method, in the way that it's needed to click on the certain League Client button// TODO Make corrections based on options, ie. click find match or back home

    // So x -> 100 and y -> 25 it's the offset to ensure that it's clicking the find match button
    x = x + 100;
    y = y + 25;

    SetCursorPos(x, y);
    // TODO Three of match decision 

    //PostMessage(hwndDesktop, WM_LBUTTONDBLCLK, 0, MAKELPARAM(x + 100, y + 25)); <--- For the client transformer coordinates window to screen
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}