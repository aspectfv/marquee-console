#pragma once
#include "SystemContext.hpp"

class CommandInterpreter {
    SystemContext& system_context_ref;

public:
    CommandInterpreter(SystemContext& context);
    void process_next_command();
};