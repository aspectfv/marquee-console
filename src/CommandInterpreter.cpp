#include "CommandInterpreter.hpp"

CommandInterpreter::CommandInterpreter(SystemContext& context) : system_context_ref(context) {}

void CommandInterpreter::process_next_command() {
    std::string command = system_context_ref.command_queue.pop().value_or("");
    if (command.empty()) return;

    if (command == "exit") system_context_ref.is_running = false;

    std::lock_guard<std::mutex> lock(system_context_ref.prompt_mutex);
    system_context_ref.prompt_display_buffer = command;
}