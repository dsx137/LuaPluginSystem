#include "head/cpphead.hpp"


PluginManager::PluginManager() {
    plugins = new std::vector<Plugin*>();
    lua = sol::state();
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string, sol::lib::table, sol::lib::math, sol::lib::io);
    // lua.new_usertype<Plugin>("Plugin",
    //     sol::constructors<Plugin(std::string, std::function<void()>, std::function<void()>, std::function<void()>)>(),
    //     "id", &Plugin::id,
    //     "Initialize", &Plugin::Initialize,
    //     "Update", &Plugin::Update,
    //     "Uninitialize", &Plugin::Uninitialize
    // );
}

PluginManager::~PluginManager() {
    Printer::Log::printLine("Unloading all plugins...");
    for (auto plugin : *plugins) {
        this->UnloadPlugin(plugin->id);
    }

    delete plugins;
}

void PluginManager::Update(std::string s) {
    for (auto plugin : *plugins) {
        try {
            plugin->Update(s);
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
            }
        }
    }
}

bool PluginManager::LoadPlugin(const std::filesystem::path& path) {
    bool runState = true;
    try {
        sol::object result = lua.do_file(path.string());
        // if (result.is<Plugin*>()) {
        //     Plugin* plugin = result.as<Plugin*>();
        //     plugins->push_back(plugin);
        //     Printer::Log::printLine("Plugin loaded: " + (std::string)plugin->id);
        //     plugin->Initialize();        
        if (result.is<sol::table>()) {
            Plugin* plugin = new Plugin(result.as<sol::table>());
            plugins->push_back(plugin);
            Printer::Log::printLine("Plugin loaded: " + (std::string)plugin->id);
            plugin->Initialize();
        } else {
            throw std::runtime_error(path.filename().string() + ": Plugin file must return a Plugin instance.");
        }
    } catch (const std::exception& e) {
        Printer::Err::printLine(e);
        runState = false;
    }

    return runState;
}

bool PluginManager::UnloadPlugin(const std::string& id) {
    bool runState = true;
    try {
        for (auto plugin : *plugins) {
            if (plugin->id == id) {
                plugin->Uninitialize();
                plugins->erase(std::remove(plugins->begin(), plugins->end(), plugin), plugins->end());
                delete plugin;
                break;
            }
        }
    } catch (const std::exception& e) {
        Printer::Err::printLine(e);
        runState = false;
    }

    return runState;
}