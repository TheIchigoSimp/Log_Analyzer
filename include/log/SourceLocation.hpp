#include <string>
#include <utility>

class SourceLocation {
    public:
        std::pair<std::string, unsigned int> parse_sourceLocation(
            const std::string &sourceLoc
        );

    private:
        std::string Source_File;
        unsigned int Line_No = 0;
};