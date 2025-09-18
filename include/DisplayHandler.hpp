#pragma once
#include "SystemContext.hpp"
#include "MarqueeLogic.hpp"

class DisplayHandler {
    SystemContext& system_context_ref;
    MarqueeLogic& marquee_logic_ref;
    
public:
    DisplayHandler(SystemContext& context, MarqueeLogic& logic);
    void run();
};