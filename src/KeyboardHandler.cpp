#include "KeyboardHandler.hpp"

#include <iostream>

KeyboardHandler::KeyboardHandler(SystemContext& context) : system_context_ref(context) {}

void KeyboardHandler::run() {
    std::string input;
    if (std::getline(std::cin, input)) system_context_ref.command_queue.push(input);
}