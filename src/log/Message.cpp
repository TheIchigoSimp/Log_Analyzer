#include<stdexcept>

#include<log/Message.hpp>

bool Message::validate_logMessage(const std::string &message){
    return !message.empty() && message.find_first_not_of(' ') != std::string::npos;
}

void Message::set_logMessage(std::string &message){
    if(!validate_logMessage(message)){
        throw std::invalid_argument("Invalid Log Message: " + message);
    }
    logMessage = message;
}

std::string Message::get_logMessage(void){
    return logMessage;
}
