#include<string>

class Message{
    public:
        std::string parse_logMessage(std::string message);
        bool validate_logMessage(const std::string &message)

    private:
        std::string logMessage;
}