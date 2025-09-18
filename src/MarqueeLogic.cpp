#include "MarqueeLogic.hpp"

MarqueeLogic::MarqueeLogic(SystemContext& context) : system_context_ref(context), display_buffer("") {}

std::string MarqueeLogic::get_next_frame() {
    return display_buffer; // placeholder 
}