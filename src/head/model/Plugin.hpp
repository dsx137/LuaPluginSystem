#include "../cpphead.hpp"

#define PLUGIN_DEFINE_FUNCTION_NAME "CreatePluginInstance"

class Plugin {
private:
    lua_State* L;
    int ref;

    void callMethod(std::string methodName) {
        lua_rawgeti(this->L, LUA_REGISTRYINDEX, ref);
        lua_getfield(this->L, -1, methodName.c_str());
        if (lua_isfunction(this->L, -1)) {
            if (lua_pcall(this->L, 0, 0, 0) == LUA_ERRRUN) {
                throw std::runtime_error(std::string(this->PLUGIN_ID) + ": " + methodName + "\n"
                    + Printer::Err::getStacktrace(L)
                );
            }
        } else {
            lua_pop(this->L, 1);
            throw std::runtime_error(std::string(this->PLUGIN_ID) + ": " + methodName + " is not found");
        }
    }

    template<typename T>
    T getAny(const std::string& name) {
        lua_rawgeti(this->L, LUA_REGISTRYINDEX, ref);
        lua_getfield(this->L, -1, name.c_str());

        T result;

        switch (lua_type(L, -1))
        {
            case LUA_TBOOLEAN:
                result = lua_toboolean(L, -1);
                break;
            case LUA_TNUMBER:
                result = lua_tonumber(L, -1);
                break;
            case LUA_TSTRING:
                result = lua_tostring(L, -1);
                break;
            default:
                throw std::runtime_error(std::string(this->PLUGIN_ID) + ": " + "Global variable " + name + " is not defined");
        }
        lua_pop(L, 1);
        return result;
    }

public:
    Property<std::string> PLUGIN_ID{ Property<std::string>(
            std::string(""),
            [&](auto value) -> auto {
                return value.empty() ? this->path.filename().string() : value;
            },
            [&](auto value, auto newValue) {
                value = newValue;
            }
    ) };

    std::filesystem::path path;

    Plugin(lua_State* L, const std::filesystem::path& path) : L(L), path(path) {
        if (luaL_dofile(this->L, path.string().c_str()) == LUA_OK) {
            lua_getglobal(this->L, PLUGIN_DEFINE_FUNCTION_NAME);
            if (lua_isfunction(this->L, -1)) {
                if (lua_pcall(this->L, 0, 1, 0) == LUA_OK) {
                    ref = luaL_ref(this->L, LUA_REGISTRYINDEX);
                    this->PLUGIN_ID = this->getAny<std::string>("PLUGIN_ID");
                } else {
                    throw std::runtime_error(
                        (std::string)this->PLUGIN_ID
                        + Printer::Err::getStacktrace(L)
                    );
                }
            } else {
                lua_pop(this->L, 1);
                throw std::runtime_error((std::string)this->PLUGIN_ID + " is not a plugin");
            }
        } else {
            throw std::runtime_error("Failed to load plugin");
        }
    }

    void Initialize() {
        callMethod("Initialize");
    }

    void Update() {
        callMethod("Update");
    }

    void Uninitialize() {
        callMethod("Uninitialize");
    }
};