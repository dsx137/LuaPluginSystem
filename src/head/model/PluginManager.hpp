#include "../cpphead.hpp"

class PluginManager {
public:
    std::vector<Plugin*>* plugins;
    PluginManager();
    ~PluginManager();
    void LoadAll();
    void UnloadAll();
    void ReloadAll();
    bool Load(const std::filesystem::path& pluginPath);
    bool Unload(const std::string& id);
    void Update(std::string s);

    sol::state lua;
};