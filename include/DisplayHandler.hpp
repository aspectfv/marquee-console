#pragma once
#include "SystemContext.hpp"
#include "MarqueeLogic.hpp"
#include "CommandInterpreter.hpp"

class DisplayHandler {
    SystemContext& system_context_ref;
    MarqueeLogic& marquee_logic_ref;
    CommandInterpreter& command_interpreter_ref;
    const int refresh_rate_ms = 50;
    
public:
    DisplayHandler(SystemContext& context, MarqueeLogic& logic, CommandInterpreter& interpreter);
    void run();
};