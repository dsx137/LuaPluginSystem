#include "head/cpphead.hpp"

std::string GetCurrentExecutableDirectory() {
    std::string directory;

#if defined(_WIN32)
    char buffer[MAX_PATH];
    DWORD result = GetModuleFileName(NULL, buffer, MAX_PATH);
    if (result != 0) {
        directory = buffer;
        size_t pos = directory.find_last_of("\\");
        if (pos != std::string::npos) {
            directory = directory.substr(0, pos);
        }
    }

#elif defined(__linux__)
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        directory = buffer;
        size_t pos = directory.find_last_of("/");
        if (pos != std::string::npos) {
            directory = directory.substr(0, pos);
        }
    }

#elif defined(__APPLE__)
    char buffer[PATH_MAX];
    uint32_t size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) == 0) {
        buffer[size] = '\0';
        directory = buffer;
        size_t pos = directory.find_last_of("/");
        if (pos != std::string::npos) {
            directory = directory.substr(0, pos);
        }
    }
#endif

    return directory;
}

// --Lua插件脚本示例
// function CreatePluginInstance()
// local plugin = {
//     --实现插件接口方法
//     Initialize = function()
//         print("Plugin initialized")
//     end,
//     Update = function()
//         print("Plugin updated")
//     end,
//     Uninitialize = function()
//         print("Plugin uninitialized")
//     end
// }

// return plugin
// end