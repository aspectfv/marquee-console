// src/CommandInterpreter.cpp

#include "CommandInterpreter.hpp"

CommandInterpreter::CommandInterpreter(SystemContext& context) : system_context_ref(context) {
    initialize_commands();
}

void CommandInterpreter::process_next_command() {
    std::optional<std::string> command_line_opt = system_context_ref.command_queue.pop();
    if (!command_line_opt) return;

    std::stringstream ss(*command_line_opt);
    std::string command;
    ss >> command;

    if (command.empty()) return;

    std::string msg;
    auto it = commands.find(command);
    if (it != commands.end()) {
        msg = it->second(ss);
    } else {
        msg = "Unknown command: '" + command + "'. Type 'help' for a list of commands.";
    }

    if (!msg.empty()) {
        std::lock_guard<std::mutex> lock(system_context_ref.prompt_mutex);
        system_context_ref.prompt_display_buffer = msg;
    }
}

void CommandInterpreter::initialize_commands() {
    commands["help"] = [](std::stringstream&) -> std::string {
        return "Commands: help, exit, start_marquee, stop_marquee, set_text <text>, set_speed <ms>";
    };

    commands["exit"] = [this](std::stringstream&) -> std::string {
        system_context_ref.is_running = false;
        return "Exiting application...";
    };

    commands["start_marquee"] = [this](std::stringstream&) -> std::string {
        system_context_ref.marquee_state.set_active(true);
        return "Marquee started.";
    };

    commands["stop_marquee"] = [this](std::stringstream&) -> std::string {
        system_context_ref.marquee_state.set_active(false);
        return "Marquee stopped.";
    };

    commands["set_text"] = [this](std::stringstream& ss) -> std::string {
        std::string text;
        std::getline(ss, text);
        if (!text.empty() && text[0] == ' ') text.erase(0, 1); // remove leading space
        
        if (text.empty()) return "Error: No text provided for set_text.";

        system_context_ref.marquee_state.set_text(text);
        return "Marquee text set to '" + text + "'.";
    };

    commands["set_speed"] = [this](std::stringstream& ss) -> std::string {
        int speed;
        if (ss >> speed && speed > 0) {
            system_context_ref.marquee_state.set_text_ms(speed);
            return "Marquee speed set to " + std::to_string(speed) + " ms.";
        }
        return "Invalid speed value. Please provide a positive number.";
    };
}