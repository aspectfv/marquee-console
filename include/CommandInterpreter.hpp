#pragma once
#include "SystemContext.hpp"
#include <unordered_map>
#include <functional>

class CommandInterpreter {
    SystemContext& system_context_ref;
    std::unordered_map<std::string, std::function<std::string(const std::string&)> > commands;

    void initialize_commands();
    std::string execute(const std::string& command);

public:
    CommandInterpreter(SystemContext& context);
    void process_next_command();
};