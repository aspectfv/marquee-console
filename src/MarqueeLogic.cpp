#include "MarqueeLogic.hpp"

MarqueeLogic::MarqueeLogic(SystemContext& context) : system_context_ref(context), display_buffer("") {}

std::string MarqueeLogic::get_next_frame() {
    MarqueeState state = system_context_ref.marquee_state.get();
    std::string text = state.get_text();

    if (text.empty()) return "";

    std::string padded_text = text + "    ";
    std::string loop_text = padded_text;

    while (loop_text.length() < view_width + text.length()) loop_text += padded_text;

    std::string frame = loop_text.substr(scroll_position % loop_text.length(), view_width);
    scroll_position = (scroll_position + 1) % loop_text.length();

    return frame;
}