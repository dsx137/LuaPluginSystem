#include "../cpphead.hpp"

class PluginManager {
public:
    std::map<std::string, Plugin*>* plugins;
    PluginManager();
    ~PluginManager();
    void LoadAllPlugins();
    bool LoadPlugin(const std::filesystem::path& pluginPath);
    void Update();

    lua_State* L;
};