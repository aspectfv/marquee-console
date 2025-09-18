#pragma once
#include "SystemContext.hpp"

class CommandInterpreter {
    SystemContext& system_context;
    std::string output_message;

public:
    CommandInterpreter(SystemContext& context);
    void process_next_command();
};