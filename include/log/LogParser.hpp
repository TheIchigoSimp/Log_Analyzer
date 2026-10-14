#include <string>

#include <log/LogRecord.hpp>

class LogParser{
    public:
    LogRecord parse_record(const std::string &log_line);
};
