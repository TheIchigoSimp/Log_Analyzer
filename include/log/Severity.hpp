#include <string>
#include <unordered_map>

class Severity{
    public:
        enum class Severity_Levels{
            DEBUG,
            INFO,
            WARNING,
            ERROR,
            UNKNOWN
        };

        bool validate_severity(const std::string &severity_str);
        void parse_to_severity_level(const std::string &severity_str);
        Severity_Levels get_severity() const;

    
    private:
        Severity_Levels severity_level_ = Severity_Levels::UNKNOWN;

        inline static const std::unordered_map<std::string, Severity_Levels> Severity_Map = {
            {"DEBUG", Severity_Levels::DEBUG},
            {"INFO", Severity_Levels::INFO},
            {"WARNING", Severity_Levels::WARNING},
            {"ERROR", Severity_Levels::ERROR},
            {"UNKNOWN", Severity_Levels::UNKNOWN}
        };
};
