#include "CommandInterpreter.hpp"
#include <sstream>

CommandInterpreter::CommandInterpreter(SystemContext& context) : system_context_ref(context) {}

void CommandInterpreter::process_next_command() {
    std::string command_line = system_context_ref.command_queue.pop().value_or("");
    if (command_line.empty()) return;

    std::stringstream ss(command_line);
    std::string command;
    ss >> command;

    std::string msg;

    if (command == "exit") {
        system_context_ref.is_running = false;
        msg = "Exiting application...";

    } else if (command == "help") {
        msg = "Commands: help, exit, start_marquee, stop_marquee, set_text <text>, set_speed <ms>";

    } else if (command == "start_marquee") {
        system_context_ref.marquee_state.set_active(true);

    } else if (command == "stop_marquee") {
        system_context_ref.marquee_state.set_active(false);
        msg = "Marquee stopped.";

    } else if (command == "set_text") {
        std::string text;
        std::getline(ss, text);
        if (!text.empty() && text[0] == ' ') text.erase(0, 1); // remove leading space
        
        system_context_ref.marquee_state.set_text(text);
        msg = "Marquee text set to " + text + ".";

    } else if (command == "set_speed") {
        int speed;

        if (ss >> speed && speed > 0) {
            system_context_ref.marquee_state.set_text_ms(speed);
            msg = "Marquee speed set to " + std::to_string(speed) + " ms.";
        } else {
            msg = "Invalid speed value.";
        }

    } else {
        msg = "Unknown command. Type 'help' for a list of commands.";
    }

    {
        std::lock_guard<std::mutex> lock(system_context_ref.prompt_mutex);
        system_context_ref.prompt_display_buffer = msg;
    }
}