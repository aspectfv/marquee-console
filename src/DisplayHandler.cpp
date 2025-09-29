#include "DisplayHandler.hpp"
#include <iostream>
#include <thread>

DisplayHandler::DisplayHandler(SystemContext& context, MarqueeLogic& logic) : system_context_ref(context), marquee_logic_ref(logic) {}

void DisplayHandler::run() {
    std::cout << "\033[2J\033[H" << "Command > " << std::flush; // clear screen and move cursor top left
    int curr_line = 1;

    while (system_context_ref.is_running) {
        if (system_context_ref.marquee_state.get_active()) {
            if (curr_line < 11) {
                int diff = 11 - curr_line;
                std::cout << "\033[" << diff << "B"; // move cursor below marquee area
                curr_line = 11;
            }

            std::cout << "\033[s" // save cursor pos
                      << "\033[1;1H" // move cursor top left
                      << marquee_logic_ref.get_next_frame() // draw marquee
                      << "\033[K" // clear to end of line
                      << "\033[u" // restore cursor to user input line
                      << std::flush;
        }

        std::string msg;
        {
            std::lock_guard<std::mutex> lock(system_context_ref.prompt_mutex);
            if (!system_context_ref.prompt_display_buffer.empty()) {
                msg = std::move(system_context_ref.prompt_display_buffer);
                system_context_ref.prompt_display_buffer.clear();
            }
        }

        if (!msg.empty()) {
          std::cout << "\n" << msg << "\nCommand > " << std::flush;
          curr_line += 2;
        }

        int speed = system_context_ref.marquee_state.get_text_ms();
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }

    std::cout << "\n" << "Exiting application..." << std::endl;
}
