#include "DisplayHandler.hpp"
#include <iostream>
#include <thread>

DisplayHandler::DisplayHandler(SystemContext& context, MarqueeLogic& logic, CommandInterpreter& interpreter) : system_context_ref(context), marquee_logic_ref(logic), command_interpreter_ref(interpreter) {}

void DisplayHandler::run() {
    while (system_context_ref.is_running) {
        MarqueeState state = system_context_ref.marquee_state.get();

        if (state.get_active()) {
            std::cout << marquee_logic_ref.get_next_frame() << std::endl;
        } else if (!system_context_ref.prompt_display_buffer.empty()) {
            std::lock_guard<std::mutex> lock(system_context_ref.prompt_mutex);
            std::cout << "Command > " << system_context_ref.prompt_display_buffer << std::endl;
            system_context_ref.prompt_display_buffer.clear();
        }

        std::cout << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(refresh_rate_ms));
    }
}