#pragma once 
#include "MarqueeState.hpp"

#include <atomic>
#include <mutex>
#include <queue>

struct SystemContext {
    MarqueeState marquee_state;
    std::queue<std::string> command_queue;
    std::atomic<bool> is_running{true};
    std::string prompt_display_buffer{};
    std::mutex prompt_mutex;
};