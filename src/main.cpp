#include <iostream>
#include "SystemContext.hpp"
#include "KeyboardHandler.hpp"

int main() {
    SystemContext context;
    KeyboardHandler keyboard_handler(context);
    keyboard_handler.run();
    return 0;
}