#include "KeyboardHandler.hpp"

#include <iostream>

void KeyboardHandler::run() {
    while (system_context_ref.is_running) {
        std::string input;
        std::getline(std::cin, input);
        system_context_ref.command_queue.push(input);
    }
}