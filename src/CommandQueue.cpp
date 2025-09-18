#include "CommandQueue.hpp"

void CommandQueue::push(const std::string& command) {
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(command);
}

std::optional<std::string> CommandQueue::pop() {
    std::lock_guard<std::mutex> lock(mutex);
    if (!queue.empty()) {
        std::string command = queue.front();
        queue.pop();

        return command;
    }

    return std::nullopt;
}