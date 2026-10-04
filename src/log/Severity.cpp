#include<log/Severity.hpp>

bool Severity::validate_severity(const std::string &severity_str){
    return Severity_Map.find(severity_str) != Severity_Map.end();
}

Severity::Severity_Levels Severity::parse_to_severity_level(const std::string &severity_str){
    if(validate_severity(severity_str)){
        return Severity_Map.at(severity_str);
    }
    return Severity_Levels::UNKNOWN;
}