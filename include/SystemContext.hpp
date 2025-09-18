#pragma once 
#include "MarqueeState.hpp"
#include "CommandQueue.hpp"

#include <atomic> 

struct SystemContext {
    MarqueeState marquee_state;
    CommandQueue command_queue;
    std::atomic<bool> is_running{true};
    std::string prompt_display_buffer{};
    std::mutex prompt_mutex;
};