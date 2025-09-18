#include "CommandInterpreter.hpp"

CommandInterpreter::CommandInterpreter(SystemContext& context) : system_context(context) {}

void CommandInterpreter::process_next_command() {
    std::string command = system_context.command_queue.pop().value_or("");

    if (command == "exit") {
        system_context.is_running = false;
        output_message = "Exiting application...";
    }
}

