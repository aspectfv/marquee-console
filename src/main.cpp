#include <iostream>
#include "SystemContext.hpp"
#include "KeyboardHandler.hpp"
#include "CommandInterpreter.hpp"
#include "MarqueeLogic.hpp"
#include <thread>


int main() {
    SystemContext context;
    
    KeyboardHandler keyboard_handler(context);
    CommandInterpreter command_interpreter(context);
    MarqueeLogic marquee_logic{context};

    std::thread keyboard_thread([&]() {
        keyboard_handler.run();
    });

    while (context.is_running) {
        command_interpreter.process_next_command();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    keyboard_thread.join();
    return 0;
}