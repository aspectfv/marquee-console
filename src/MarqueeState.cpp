#include "MarqueeState.hpp"

MarqueeState::MarqueeState(std::string text, int text_ms, bool is_active) : text(std::move(text)), text_ms(text_ms), is_active(is_active) {}

MarqueeState MarqueeState::get() {
    std::lock_guard<std::mutex> lock(mutex);
    return MarqueeState(text, text_ms, is_active);
}

void MarqueeState::setText(const std::string& newText) {
    std::lock_guard<std::mutex> lock(mutex);
    text = newText;
}

void MarqueeState::setActive(bool newActive) {
    std::lock_guard<std::mutex> lock(mutex);
    is_active = newActive;
}

void MarqueeState::setTextMs(int newTextMs) {
    std::lock_guard<std::mutex> lock(mutex);
    text_ms = newTextMs;
}
