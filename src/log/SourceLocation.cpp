#include <limits>
#include <regex>
#include <stdexcept>
#include <string>
#include <utility>

#include "log/SourceLocation.hpp"

namespace {
bool validate_source_file(const std::string &source_file)
{
    return !source_file.empty();
}

bool validate_line_no(const std::string &line_number)
{
    try {
        const unsigned long parsed_line = std::stoul(line_number);
        return parsed_line <= std::numeric_limits<unsigned int>::max();
    } catch (const std::exception &) {
        return false;
    }
}
}

std::pair<std::string, unsigned int> SourceLocation::parse_sourceLocation(
    const std::string &sourceLoc
)
{
    const std::regex pattern(R"(^\{([^:{}]+):([1-9][0-9]*)\}$)");
    std::smatch match;

    if (!std::regex_match(sourceLoc, match, pattern)) {
        throw std::invalid_argument("Invalid SourceLocation: " + sourceLoc);
    }

    Source_File = match[1].str();
    const std::string line_number = match[2].str();

    if (!validate_source_file(Source_File)) {
        throw std::invalid_argument("Invalid Source File: " + Source_File);
    }
    if (!validate_line_no(line_number)) {
        throw std::invalid_argument("Invalid Line Number: " + line_number);
    }

    Line_No = static_cast<unsigned int>(std::stoul(line_number));
    return {Source_File, Line_No};
}