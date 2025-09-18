#include "DisplayHandler.hpp"
#include <iostream>
#include <thread>

DisplayHandler::DisplayHandler(SystemContext& context, MarqueeLogic& logic) : system_context_ref(context), marquee_logic_ref(logic) {}

void DisplayHandler::run() {
    std::cout << "\033[2J\033[H" << "Command > " << std::flush; // clear screen and move cursor top left

    while (system_context_ref.is_running) {
        if (system_context_ref.marquee_state.get_active()) {
            std::cout << "\033[s"      // save cursor pos
                      << "\033[1;1H"   // move cursor top left
                      << marquee_logic_ref.get_next_frame() // draw marquee
                      << "\033[K"      // clear to end of line
                      << "\033[u"      // restore cursor to user input line
                      << std::flush;
        }

        std::string msg;
        {
            std::lock_guard<std::mutex> lock(system_context_ref.prompt_mutex);
            if (!system_context_ref.prompt_display_buffer.empty()) {
                msg = std::move(system_context_ref.prompt_display_buffer);
            }
        }

        if (!msg.empty()) std::cout << "\n" << msg << "\nCommand > " << std::flush;

        std::this_thread::sleep_for(std::chrono::milliseconds(refresh_rate_ms));
    }
}