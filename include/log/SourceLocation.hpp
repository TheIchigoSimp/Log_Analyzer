#include <string>
#include <utility>

class SourceLocation {
    public:
        void parse_sourceLocation(
            const std::string &sourceLoc
        );
        std::pair<std::string, unsigned int> get_sourceLoc(void);

    private:
        std::string Source_File;
        unsigned int Line_No = 0;
};
