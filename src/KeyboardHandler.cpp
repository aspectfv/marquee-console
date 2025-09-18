#include "KeyboardHandler.hpp"

#include <iostream>

KeyboardHandler::KeyboardHandler(SystemContext& context) : system_context_ref(context) {}

void KeyboardHandler::run() {
    std::string input;
    while (system_context_ref.is_running && std::getline(std::cin, input)) {
        if (!input.empty()) system_context_ref.command_queue.push(input);
    }
}