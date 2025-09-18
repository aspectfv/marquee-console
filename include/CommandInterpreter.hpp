#pragma once
#include "SystemContext.hpp"
#include <unordered_map>
#include <functional>
#include <sstream>

class CommandInterpreter {
    SystemContext& system_context_ref;
    std::unordered_map<std::string, std::function<std::string(std::stringstream&)>> commands;

    void initialize_commands();

public:
    CommandInterpreter(SystemContext& context);
    void process_next_command();
};