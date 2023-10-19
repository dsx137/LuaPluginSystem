#include "head/cpphead.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    PluginManager pluginManager;
    pluginManager.LoadAllPlugins();
    // while (true)
    // {
    //     pluginManager.Update();
    // }
    return 0;
}