#include "head/cpphead.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    PluginManager pluginManager;
    pluginManager.LoadAllPlugins();
    while (true)
    {
        std::string s;
        std::cin >> s;
        pluginManager.Update(s);
    }
    return 0;
}