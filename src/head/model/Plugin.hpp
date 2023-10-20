#include "../cpphead.hpp"

#define PLUGIN_DEFINE_FUNCTION_NAME "CreatePluginInstance"

class Plugin {
private:
    sol::table pluginTable;
public:
    std::string id;


    Plugin(sol::table pluginTable) {
        this->pluginTable = pluginTable;
        this->id = pluginTable["id"];
    }

    void Initialize() {
        pluginTable["Initialize"](pluginTable);
    };

    template<typename T>
    void Update(T s) {
        pluginTable["Update"](pluginTable, s);
    };

    void Uninitialize() {
        pluginTable["Uninitialize"](pluginTable);
    };
};