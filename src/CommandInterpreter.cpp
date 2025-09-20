#include "CommandInterpreter.hpp"

#include <sstream>

CommandInterpreter::CommandInterpreter(SystemContext& context) : system_context_ref(context) { initialize_commands(); }

std::string CommandInterpreter::execute(const std::string& command_line) {
    std::istringstream iss(command_line);
    std::string command;
    iss >> command;
    std::string args;
    std::getline(iss, args);

    std::string msg;
    auto it = commands.find(command);

    if (it != commands.end()) {
        msg = it->second(args);
    } else {
        msg = "Unknown command: '" + command + "'. Type 'help' for a list of commands.";
    }

    return msg;
}

void CommandInterpreter::process_next_command() {
    if (system_context_ref.command_queue.empty()) return;

    std::string command_line = system_context_ref.command_queue.front();
    system_context_ref.command_queue.pop();

    std::string msg = execute(command_line);

    if (!msg.empty()) {
        std::lock_guard<std::mutex> lock(system_context_ref.prompt_mutex);
        system_context_ref.prompt_display_buffer = msg;
    }
}

void CommandInterpreter::initialize_commands() {
    commands["help"] = [](const std::string& args) -> std::string {
        return "Commands: help, exit, start_marquee, stop_marquee, set_text <text>, set_speed <ms>";
    };

    commands["exit"] = [this](const std::string& args) -> std::string {
        system_context_ref.is_running = false;
        return "Exiting application...";
    };

    commands["start_marquee"] = [this](const std::string& args) -> std::string {
        system_context_ref.marquee_state.set_active(true);
        return "Marquee started.";
    };

    commands["stop_marquee"] = [this](const std::string& args) -> std::string {
        system_context_ref.marquee_state.set_active(false);
        return "Marquee stopped.";
    };

    commands["set_text"] = [this](const std::string& args) -> std::string {
        std::string text = args;

        if (!text.empty() && text[0] == ' ') text.erase(0, 1);
        if (text.empty()) return "Error: No text provided for set_text.";
        
        system_context_ref.marquee_state.set_text(text);
        return "Marquee text set to '" + text + "'.";
    };

    commands["set_speed"] = [this](const std::string& args) -> std::string {
        std::istringstream ss(args);
        int speed;
        if (ss >> speed && speed > 0) {
            system_context_ref.marquee_state.set_text_ms(speed);
            return "Marquee speed set to " + std::to_string(speed) + " ms.";
        }
        return "Invalid speed value. Please provide a positive number.";
    };
}