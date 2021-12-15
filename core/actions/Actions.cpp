#include "Actions.hpp"
#include "../league_client/LeagueClientButton.hpp"
#include "../../window_capture/WindowCapture.h"
#include "../../vision/RumbleVision.h"

/**
 * File that contains the Rumble predefined actions
 * 
 */

// Simple actions

/**
 * Simulated the mouse click on a League of Legends Client button
 * if the button it's found on the screen
 * 
 */
class ClickScreenButtonBuilder
{
    private:
        const ClientButton* const& client_button;
};

// TODO Construct the object with a builder
class ClickScreenButton : public I_SimpleAction 
{
    private:
        // Constant reference to a constant ClientButton pointer
        const ClientButton* const& client_button;
        const WindowCapture* window_capture;
        const RumbleLeagueVision* rumble_vistion;

    public:
        ClickScreenButton(const ClientButton* const& client_button)
        : client_button{ client_button } 
        {
            window_capture = new WindowCapture( "League of Legends" );
        }

        virtual void run_action() override 
        {
            // TODO Provide implementation
        }
};