print("woce")
-- Lua插件脚本示例
function CreatePluginInstance()
    local plugin = {
        -- 实现插件接口方法
        Initialize = function()
            print("Plugin initialized")
        end,
        Update = function()
            print("Plugin updated")
        end,
        Uninitialize = function()
            print("Plugin uninitialized")
        end
    }

    return plugin
end
