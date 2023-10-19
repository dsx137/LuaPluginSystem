#include "head/cpphead.hpp"


PluginManager::PluginManager() {
    plugins = new std::map<std::string, Plugin*>();
    L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_base(L);
    luaopen_string(L);
    luaopen_table(L);
    luaL_openlibs(L);
    luaopen_math(L);
}

PluginManager::~PluginManager() {
    Printer::Log::printLine("Unloading plugins...");
    for (auto plugin : *plugins) {
        try {
            plugin.second->Uninitialize();
        } catch (const std::exception& e) {
            Printer::Err::printLine(e);
        }
        delete plugin.second;
    }

    delete plugins;
    lua_close(this->L);
}

void PluginManager::Update() {
    for (auto plugin : *plugins) {
        try {
            plugin.second->Update();
        } catch (const std::exception& e) {
            Printer::Err::printLine(e);
        }
    }
}

void PluginManager::LoadAllPlugins() {

    std::filesystem::path pluginPath = GetCurrentExecutableDirectory() + "/plugin";
    if (!std::filesystem::is_directory(pluginPath)) {
        std::filesystem::create_directory(pluginPath);
    } else {
        for (const auto& entry : std::filesystem::directory_iterator(pluginPath)) {
            if (entry.is_regular_file() && entry.path().extension() == ".lua") {
                this->LoadPlugin(entry.path());
                std::cout << lua_tostring(this->L, -1) << std::endl;
            }
        }
    }
}

bool PluginManager::LoadPlugin(const std::filesystem::path& path) {
    bool runState = true;
    try {
        Plugin* plugin = new Plugin(this->L, path);
        plugins->emplace(plugin->PLUGIN_ID, plugin);
        Printer::Log::printLine("Plugin loaded: " + (std::string)plugin->PLUGIN_ID);
        plugin->Initialize();
    } catch (const std::exception& e) {
        Printer::Err::printLine(e);
        runState = false;
    }

    return runState;
}
