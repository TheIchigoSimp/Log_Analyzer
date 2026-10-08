#include<log/Severity.hpp>

bool Severity::validate_severity(const std::string &severity_str){
    return Severity_Map.find(severity_str) != Severity_Map.end();
}

void Severity::parse_to_severity_level(const std::string &severity_str){
    if(validate_severity(severity_str)){
        severity_level_ = Severity_Map.at(severity_str);
        return;
    }
    severity_level_ = Severity_Levels::UNKNOWN;
}

Severity::Severity_Levels Severity::get_severity() const{
    return severity_level_;
}

