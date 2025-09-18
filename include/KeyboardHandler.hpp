#pragma once
#include "SystemContext.hpp"

class KeyboardHandler {
    SystemContext& system_context_ref;

public:
    KeyboardHandler(SystemContext& context) : system_context_ref(context) {}
    void run();
};