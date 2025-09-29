#include "MarqueeState.hpp"
#include "AsciiArtMapper.hpp"

MarqueeState::MarqueeState() : text(AsciiArtMapper::to_ascii_art("Welcome to CSOPESY!")), text_ms(50), is_active(false) {}

MarqueeState::MarqueeState(const std::string& text, int text_ms, bool is_active)
    : text(text), text_ms(text_ms), is_active(is_active) {}

MarqueeState MarqueeState::get() {
    std::lock_guard<std::mutex> lock(mutex);
    return MarqueeState(text, text_ms, is_active);
}

std::string MarqueeState::get_text() {
    std::lock_guard<std::mutex> lock(mutex);
    return text;
}

int MarqueeState::get_text_ms() {
    std::lock_guard<std::mutex> lock(mutex);
    return text_ms;
}

bool MarqueeState::get_active() {
    std::lock_guard<std::mutex> lock(mutex);
    return is_active;
}

void MarqueeState::set_text(const std::string& newText) {
    std::lock_guard<std::mutex> lock(mutex);
    text = newText;
}

void MarqueeState::set_active(bool newActive) {
    std::lock_guard<std::mutex> lock(mutex);
    is_active = newActive;
}

void MarqueeState::set_text_ms(int newTextMs) {
    std::lock_guard<std::mutex> lock(mutex);
    text_ms = newTextMs;
}
