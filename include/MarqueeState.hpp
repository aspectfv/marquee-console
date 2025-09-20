#pragma once
#include <string>
#include <mutex>

class MarqueeState {
    std::string text;
    std::mutex mutex;

    int text_ms;
    bool is_active;

public: 
    MarqueeState();
    MarqueeState(const std::string& text, int text_ms, bool is_active);
    MarqueeState get();
    std::string get_text();
    int get_text_ms();
    bool get_active();
    void set_text(const std::string& newText);
    void set_active(bool newActive);
    void set_text_ms(int newTextMs);
};