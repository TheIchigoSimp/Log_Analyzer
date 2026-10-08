#include<log/LogRecord.hpp>

std::chrono::system_clock::time_point LogRecord::get_timestamp_tm(void){
    return timestamp.get_time_tm();
}

std::string LogRecord::get_timestamp_str(void){
    return timestamp.get_time_str();
}

std::pair<std::string, unsigned int> LogRecord::get_sourcelocation(void){
    return sourcelocation.get_sourceLoc();
}

Severity::Severity_Levels LogRecord::get_severity_level(void){
    return severity.get_severity();
}

std::string LogRecord::get_message(void){
    message.get_logMessage();
}
