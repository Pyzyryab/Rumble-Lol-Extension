#include "opencv2/opencv.hpp"

#include "Actions.hpp"
#include "../league_client/LeagueClientButton.hpp"
#include "../../vision/RumbleVision.hpp"
#include "../../motion/RumbleMotion.hpp"
#include "../../window_capture/WindowCapture.hpp"


/**
 * Simulates the mouse click on a League of Legends Client button
 * if the button it's found on the screen
 */
class ClickScreenButton : public I_SimpleAction
{
    private:
        // Constant reference to a constant ClientButton pointer
        const ClientButton* const& client_button;

        /*
		* Declares our helper to get the video source
		* BIG TODO -> On the named constructor, should implement a way to converse coordinates from a captured window,
		* ie, the League of Legends window, instead of capturing the whole screen. Second way it's the implemented right now,
		* because the match location also matches where the program should make the mouse click action.
		* The W2 lib has a method that converts the internal window coordinates(Client) to Screen coordinates 
		* -> ::ClientToScreen( hwndDesktop, mouse_click_point_ptr );
		*/
		WindowCapture* window_capture;

		/*
		* Rumble Vision.Tools for simulate vision skills for Rumble AI.The main goal of this object
		* it's to interface the "find" method, that will locate the images of the League Client on the screen
		* that will match the image that we need to perform an action
		*/
		RumbleLeagueVision* rumble_vision;

		/*
		* Designed to encapsulate the final behaviour of a move and click action on the RumbleLeague object.
		* This method receives a needle image and inmedialy tries to found it on the video source,
		* WITHOUT waiting for the image to appear on the screen. This method it's intented to use in basic situations
		* on click buttons that always are on the screen (basically, all buttons) with the exception of those who
		* has to be awaited to found them. One example is the "Accept" game button or the "Decline" game button.
		* For actions like this, please, refer to the ::wait_event() method.
		*/
		cv::Point click_event(const cv::Mat& needle_image);

		/*
		* The continuos waiting until a 'button' on the screen appears implementation of a click event
		*/
		void wait_event(const cv::Mat& needle_image);

    public:
        ClickScreenButton(const ClientButton* const& client_button);
        virtual ~ClickScreenButton() override;
        virtual void run_action() override;
};