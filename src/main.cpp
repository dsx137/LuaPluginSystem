#include "head/cpphead.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    PluginManager pluginManager;
    pluginManager.LoadAll();
    while (true)
    {
        std::string s;
        std::cin >> s;
        if (s == "/reload") {
            pluginManager.ReloadAll();
            continue;
        } else if (s == "/exit") {
            break;
        } else if (s == "/plugins") {
            for (auto plugin : *pluginManager.plugins) {
                std::cout << plugin->id << std::endl;
            }
            continue;
        }
        pluginManager.Update(s);
    }
    return 0;
}