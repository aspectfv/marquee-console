#pragma once 
#include "MarqueeState.hpp"
#include "CommandQueue.hpp"

struct SystemContext {
    MarqueeState marquee_state;
    CommandQueue command_queue;
    std::atomic<bool> is_running{true};
};