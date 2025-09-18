#pragma once

#include "SystemContext.hpp"

class MarqueeLogic {
    SystemContext& system_context_ref;
    std::string display_buffer;

public:
    MarqueeLogic(SystemContext& context);
    std::string get_next_frame();
};