#include "../cpphead.hpp"

class PluginManager {
public:
    std::vector<Plugin*>* plugins;
    PluginManager();
    ~PluginManager();
    void LoadAllPlugins();
    bool LoadPlugin(const std::filesystem::path& pluginPath);
    bool UnloadPlugin(const std::string& id);
    void Update(std::string s);

    sol::state lua;
};