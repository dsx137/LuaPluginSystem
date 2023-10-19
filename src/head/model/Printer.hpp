#include "../cpphead.hpp"

class Printer {
public:
    enum MESSAGE_TYPE {
        INFO,
        WARNING,
        ERR
    };
    static std::string getMessageTypeName(MESSAGE_TYPE type) {
        switch (type) {
            case INFO:
                return "INFO";
            case WARNING:
                return "WARNING";
            case ERR:
                return "ERR";
            default:
                return "UNKNOWN";
        }
    }

    static std::string getPrefix(MESSAGE_TYPE type) {
        return "[" + getMessageTypeName(type) + "] ";
    }

    class Err {
    public:
        static void printLine(const std::exception& e) {
            std::cerr << Printer::getPrefix(Printer::MESSAGE_TYPE::ERR)
                << "Exception caught: " << e.what() << std::endl;
        }

        static std::string getStacktrace(lua_State* L) {
            const char* traceInfo = lua_tostring(L, -1);
            if (!traceInfo || traceInfo[0] == '\0') {
                return "";
            }

            lua_pop(L, 1);

            std::stringstream ss(traceInfo);
            std::string line, result = "\tstack traceback:\n";
            while (std::getline(ss, line)) {
                result += "\t\t" + line + "\n";
            }
            return result;
        }
    };
    class Log {
    public:
        static void printLine(const std::string& info) {
            std::clog << Printer::getPrefix(Printer::MESSAGE_TYPE::INFO) << info << std::endl;
        }
    };
};