#include "ClickScreenButton.hpp"
#include "../../window_capture/WindowCapture.hpp"
#include "../../vision/RumbleVision.hpp"
#include "../../motion/RumbleMotion.hpp"
#include "../../data/constants.hpp"

/**
 * Simulated the mouse click on a League of Legends Client button
 * if the button it's found on the screen
 */

ClickScreenButton::ClickScreenButton(const ClientButton* const& client_button)
    : client_button{ client_button } 
{
    window_capture = new WindowCapture{ "League of Legends" };
}

ClickScreenButton::~ClickScreenButton()
{
    std::cout << "Deleting 'Action type' of subtype 'Simple' for ClickScreenButton implementor" << std::endl;
}

void ClickScreenButton::run_action()
{
    cv::Mat needle_image;
    cv::Mat img_to_find = cv::imread(client_button->image_path, cv::IMREAD_COLOR);
    cvtColor(img_to_find, needle_image, cv::COLOR_BGR2BGRA);

    // Controls when an even should be awaited (until appears on screen) or not.
    (!client_button->is_waiting_button) 
        ? this->click_event(needle_image) 
        : this->wait_event(needle_image);
}

/*
* Designed to encapsulate the final behaviour of a move and click action on the RumbleLeague object.
* This method receives a needle image and inmedialy tries to found it on the video source, 
* WITHOUT waiting for the image to appear on the screen. This method it's intented to use in basic situations
* on click buttons that always are on the screen (basically, all buttons) with the exception of those who 
* has to be awaited to found them. One example is the "Accept" game button or the "Decline" game button.
* For actions like this, please, refer to the ::wait_event() method.
*/
cv::Point ClickScreenButton::click_event(const cv::Mat& needle_image)
{
    cv::Mat video_source = this->window_capture->get_video_source();
    cv::Mat* video_source_ptr = &video_source;

    // Img finder. Matches the video source and the needle image and returns the point where the needle image is found inside the video source.
    cv::Point m_loc = this->rumble_vision->find(
        video_source_ptr, 
        needle_image, 
        Constants::THRESHOLD_RATE, 
        Constants::TITLEBAR_WINDOW_NAME
    );


    if (m_loc.x != 0 && m_loc.y != 0)
    {
        // Copy the data from the openCV Point type to the POINT type from the Windows API
        POINT coords { m_loc.x, m_loc.y };

        // Transform the match location coordinates into the relative coordinates 
        // of the current machine desktop screen
        // Details: https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-clienttoscreen
        ::ClientToScreen(this->window_capture->get_hwnd(), &coords);

        std::cout << "MATCH LOCATION (Windowed) -> " << m_loc << std::endl;
        std::cout << "MATCH LOCATION -> [" << coords.x << " , " << coords.y << "]" << std::endl;

        RumbleMotion* rumble_motion = new RumbleMotion();
        rumble_motion->move_mouse_and_left_click(coords.x, coords.y);
        delete rumble_motion;
    }

    return m_loc;
}


void ClickScreenButton::wait_event(const cv::Mat& needle_image)
{
    int key = 0;
    while (key != 27) // 'ESC' key // TODO Check if the key works on wait events or should be replaced by a while True
    {
        if (this->click_event(needle_image) != cv::Point{ 0, 0 })
        { 
            break; 
        }
        key = cv::waitKey(60); // you can change wait time. Need a large value when the find game it's detected?
    }
}