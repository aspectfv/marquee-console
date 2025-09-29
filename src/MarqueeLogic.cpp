#include "MarqueeLogic.hpp"
#include <sstream>
#include <vector>
#include <algorithm>

MarqueeLogic::MarqueeLogic(SystemContext& context) : system_context_ref(context), display_buffer("") {}

std::string MarqueeLogic::get_next_frame() {
    MarqueeState state = system_context_ref.marquee_state.get();
    std::string text = state.get_text();

    if (text.empty()) return "";

    // split text into lines
    std::vector<std::string> lines;
    std::istringstream text_stream(text);
    std::string line;
    while (std::getline(text_stream, line)) {
        lines.push_back(line);
    }

    if (lines.empty()) return "";

    // find width of longest line in ascii art
    size_t text_width = 0;
    for (const auto& l : lines) {
        text_width = std::max(text_width, l.length());
    }

    const std::string separator = "    ";
    const size_t padded_width = text_width + separator.length();

    std::ostringstream result_frame;
    for (size_t i = 0; i < lines.size(); ++i) {
        std::string current_line = lines[i];
        // pad current line to ensure all lines have same length
        current_line.append(text_width - current_line.length(), ' ');

        std::string padded_line = current_line + separator;
        
        // create long string to scroll through by repeating the padded line
        std::string loop_line = padded_line;
        while (loop_line.length() < view_width + padded_width) {
            loop_line += padded_line;
        }

        // get portion of line for current frame
        std::string frame_part = loop_line.substr(scroll_position % padded_width, view_width);
        result_frame << frame_part;
        if (i < lines.size() - 1) {
            result_frame << "\n";
        }
    }

    // increment scroll position for next frame
    scroll_position++;

    return result_frame.str();
}
