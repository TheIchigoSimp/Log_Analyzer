#include<string>

class Message{
    public:
        bool validate_logMessage(const std::string &);
        void set_logMessage(std::string&);
        std::string get_logMessage(void);

    private:
        std::string logMessage;
};
