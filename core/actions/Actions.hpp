#pragma once

#include "opencv2/opencv.hpp"
#include "../league_client/LeagueClientButton.hpp"

/**
 * Interface that defines the content of the behaviour of an action
 */
class Action 
{
    // TODO Implement the action Factory
    public:
        // Pure virtual method definitions
        virtual void run_action() = 0;
};

/**
* Provides a way to interface and define what a simple action is.
* 
* A simple action it's a way to declare a Rumble's type of action like click 
* on the screen, write text to the screen, scroll some sort of scrollable item...
*/
class I_SimpleAction : public Action 
{
    public:
        virtual ~I_SimpleAction() {}
};

/**
 * A complex action it's just the sum of many "I_SimpleAction" that performs a complex
 * task, like the automatation of pick or ban a champ, select summoners,
 * select a game mode directly from any place and so forth.
 */
class I_ComplexAction : public Action
{
    public:
        virtual ~I_ComplexAction() {}
};