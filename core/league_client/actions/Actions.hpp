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
        virtual void get_action_identifiers() = 0;
        virtual ~I_Action() {}
};


class I_SimpleAction : public I_Action 
{
    private:
        const char* identifiers[1];
    public:
        virtual ~I_SimpleAction() {}
};

class I_ComplexAction : public I_Action
{
    private:
        const char* identifiers[1];
    public:
        virtual ~I_ComplexAction() {}
};