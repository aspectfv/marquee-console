#pragma once
#include <queue>
#include <mutex>
#include <string>
#include <optional>

class CommandQueue {
    std::queue<std::string> queue;
    std::mutex mutex;

public:
    void push(const std::string& command);
    std::optional<std::string> pop();
};