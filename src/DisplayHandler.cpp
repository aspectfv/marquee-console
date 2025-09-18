#include "DisplayHandler.hpp"
#include <iostream>
#include <thread>

DisplayHandler::DisplayHandler(SystemContext& context, MarqueeLogic& logic, CommandInterpreter& interpreter) : system_context_ref(context), marquee_logic_ref(logic), command_interpreter_ref(interpreter) {}

void DisplayHandler::run() {
    std::string last_message;

    while (system_context_ref.is_running) {
        this->clearScreen();
        MarqueeState state = system_context_ref.marquee_state.get();

        if (state.get_active()) {
            std::cout << marquee_logic_ref.get_next_frame() << std::endl;
        } else {
            std::string message;
            {
                std::lock_guard<std::mutex> lock(system_context_ref.prompt_mutex);
                message = system_context_ref.prompt_display_buffer;
            }

            if (message != last_message) {
                last_message = message;
                std::cout << "Command > " << message << std::endl;
            }
        }

        std::cout << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(refresh_rate_ms));
    }
}

void DisplayHandler::clearScreen() {
    std::cout << "\033[2J\033[H";
}