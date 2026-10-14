#include <regex>
#include <stdexcept>
#include <string>

#include <log/LogParser.hpp>

LogRecord LogParser::parse_record(const std::string &log_line)
{
    static const std::regex record_pattern(
        "^(\\[[0-9]{4}-[0-9]{2}-[0-9]{2}, [0-9]{2}:[0-9]{2}:[0-9]{2} UTC\\]) +"
        "(\\{[^{}]+\\}) +(DEBUG|INFO|WARNING|ERROR|UNKNOWN) +(.+)$"
    );
    std::smatch match;

    if (!std::regex_match(log_line, match, record_pattern)) {
        throw std::invalid_argument("Invalid log record: " + log_line);
    }

    Timestamp timestamp;
    timestamp.parse_to_tm(match[1].str());
    timestamp.parse_to_str(timestamp.get_time_tm());

    SourceLocation source_location;
    source_location.parse_sourceLocation(match[2].str());

    Severity severity;
    severity.parse_to_severity_level(match[3].str());

    Message message;
    std::string message_text = match[4].str();
    message.set_logMessage(message_text);

    return LogRecord(timestamp, source_location, severity, message);
}
