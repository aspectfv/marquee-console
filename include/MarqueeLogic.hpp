#pragma once

#include "SystemContext.hpp"

class MarqueeLogic {
    SystemContext& system_context_ref;
    std::string display_buffer;
    int scroll_position = 0;
    const int view_width = 50;

public:
    MarqueeLogic(SystemContext& context);
    std::string get_next_frame();
};