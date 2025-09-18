#include "DisplayHandler.hpp"
#include <iostream>
#include <thread>

DisplayHandler::DisplayHandler(SystemContext& context, MarqueeLogic& logic) : system_context_ref(context), marquee_logic_ref(logic) {}

void DisplayHandler::run() {
    auto clearScreen = []() { std::cout << "\033[2J\033[H"; };

    while (system_context_ref.is_running) {
        bool is_marquee_active = system_context_ref.marquee_state.get().get_active();

        if (is_marquee_active) {
            std::cout << marquee_logic_ref.get_next_frame() << std::endl;
        } else {
            std::string msg;
            {
                std::lock_guard<std::mutex> lock(system_context_ref.prompt_mutex);
                msg = std::move(system_context_ref.prompt_display_buffer); // consume msg
            }

            if (!msg.empty()) {
                std::cout << msg << std::endl;
                std::cout << "Command > " << std::endl;
            }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(refresh_rate_ms));
    }
}