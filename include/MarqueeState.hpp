#pragma once
#include <string>
#include <mutex>

class MarqueeState {
    std::string text;
    int text_ms;
    bool is_active;
    std::mutex mutex;

public: 
    MarqueeState(std::string text, int text_ms, bool is_active);
    MarqueeState get();

    void setText(const std::string& newText);
    void setActive(bool newActive);
    void setTextMs(int newTextMs);
};