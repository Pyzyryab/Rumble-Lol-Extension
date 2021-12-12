#pragma once

/**
 * Interface that defines the content of the behaviour of an action
 */
class I_Action 
{
    private:
        const char* identifiers[1]; 
    public:
        // Pure virtual method definitions
        virtual void run_action() = 0;
        // virtual void get_action_identifiers() = 0;
        virtual ~I_Action() {}
};

/**
* Provides a way to interface and define what a simple action is.
* 
* A simple action it's a way to declare a Rumble's type of action like click 
* on the screen, write text to the screen, scroll some sort of scrollable item...
*/
class I_SimpleAction : public I_Action 
{
    private:
        const char* identifiers[1];
    public:
        virtual ~I_SimpleAction() {}
};

/**
 * A complex action it's just the sum of many "I_SimpleAction" that performs a complex
 * task, like the automatation of pick or ban a champ, select summoners,
 * select a game mode directly from any place and so forth.
 */
class I_ComplexAction : public I_Action
{
    private:
        const char* identifiers[1];
    public:
        virtual ~I_ComplexAction() {}
};