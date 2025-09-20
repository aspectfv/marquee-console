// src/main.cpp

#include "SystemContext.hpp"
#include "KeyboardHandler.hpp"
#include "CommandInterpreter.hpp"
#include "MarqueeLogic.hpp"
#include "DisplayHandler.hpp"
#include <iostream>
#include <thread>

const int refresh_rate_ms = 10;

int main() {
    SystemContext context;
    
    KeyboardHandler keyboard_handler(context);
    CommandInterpreter command_interpreter(context);
    MarqueeLogic marquee_logic(context);
    DisplayHandler display_handler(context, marquee_logic);

    std::thread display_thread(&DisplayHandler::run, &display_handler);

    while (context.is_running) {
        keyboard_handler.run();
        command_interpreter.process_next_command();
        std::this_thread::sleep_for(std::chrono::milliseconds(refresh_rate_ms));
    }

    if (display_thread.joinable()) display_thread.join();
    return 0;
}