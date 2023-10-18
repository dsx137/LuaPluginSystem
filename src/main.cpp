#include "head/cpphead.h"

// void LoadPlugin(const std::string& pluginPath) {
//     // 创建Lua状态
//     lua_State* L = luaL_newstate();
//     luaL_openlibs(L);

//     // 加载Lua插件脚本
//     if (luaL_loadfile(L, pluginPath.c_str()) == LUA_OK) {
//         // 执行Lua脚本
//         lua_pcall(L, 0, 0, 0);

//         // 获取Lua函数
//         lua_getglobal(L, "CreatePluginInstance");
//         if (lua_isfunction(L, -1)) {
//             // 创建插件实例
//             Plugin* plugin = reinterpret_cast<Plugin*>(lua_touserdata(L, -1));
//             if (plugin) {
//                 plugin->Initialize();
//                 plugins.push_back(plugin);
//             }
//         }
//     }

//     lua_close(L);
// }

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << GetCurrentExecutableDirectory() << std::endl;
    lua_State* lua = luaL_newstate();
    luaL_openlibs(lua);

    luaopen_base(lua);
    //打开string库（使用string时需要打开）
    luaopen_string(lua);
    //打开table库
    luaopen_table(lua);
    //打开IO库
    luaL_openlibs(lua);
    //打开math库
    luaopen_math(lua);

    std::string pluginPath = GetCurrentExecutableDirectory() + "/plugin";


    if (!std::filesystem::is_directory(pluginPath)) {
        std::filesystem::create_directory(pluginPath);
    }
    else {
        for (const auto& entry : std::filesystem::directory_iterator(pluginPath)) {
            if (entry.is_regular_file() && entry.path().extension() == ".lua") {
                if (luaL_loadfile(lua, entry.path().string().c_str()) != LUA_OK) {
                    std::cout << lua_tostring(lua, -1) << std::endl;
                }
                else {
                    lua_pcall(lua, 0, 0, 0);
                }
            }
        }
    }
    lua_close(lua);
    return 0;
}