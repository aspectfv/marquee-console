#include "AsciiArtMapper.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::string AsciiArtMapper::to_ascii_art(const std::string& text) {
    std::vector<std::string> lines;

    for (char c : text) {
        std::ifstream file(std::string("art/") + c + ".txt");
        if (!file) continue;

        std::vector<std::string> charLines;
        std::string line;

        while (std::getline(file, line)) {
            charLines.push_back(line);
        }

        if (lines.empty()) {
            lines = charLines;
        } else {
            // append side by side
            for (size_t i = 0; i < lines.size(); i++) {
                if (i < charLines.size()) {
                    lines[i] += " " + charLines[i];
                } else {
                    lines[i] += " ";
                }
            }
        }
    }

    std::ostringstream result;
    for (const auto& l : lines) {
        result << l << "\n";
    }

    return result.str();
}

