#pragma once

#include <sol/sol.hpp>

struct ScriptEngine {
    ScriptEngine();

    bool runLuaString(const std::string &script);
    bool runLuaFile(const std::string &path);

    /**
     * @brief Gets a Lua function
     *  This would be a function that already exists, usually by running the
     * .lua script files Bare in mind, it will only find functions that belong
     * to OpenBuilder (aka in 'game' lua global table)
     * @param functionName The name of the function to find
     * @return sol::function The Lua function
     */
    sol::function getLuaFunction(const char *functionName);

    template <typename... Args>
    auto addTable(const std::string &tableName, Args &&... args);

    template <typename T, typename... Args>
    auto addType(const std::string &name, Args &&... args);

    sol::state lua;
    sol::table gameTable;
};

template <typename T, typename... Args>
auto ScriptEngine::addType(const std::string &name, Args &&... args)
{
    return lua.new_usertype<T>(name, std::forward<Args>(args)...);
}

template <typename... Args>
auto ScriptEngine::addTable(const std::string &tableName, Args &&... args)
{
    return gameTable.create_named(tableName, std::forward<Args>(args)...);
}