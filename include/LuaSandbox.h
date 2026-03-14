#pragma once

#include <string>
#include <functional>
#include <map>
#include <memory>

#include "LuaRef.h"

struct lua_State;

namespace LuaWrapper {
    class LuaStack;

    class LuaSandbox
    {
    public:
        explicit LuaSandbox(LuaStack* stack);
        LuaSandbox(const LuaSandbox&) = default;
        LuaSandbox(LuaSandbox&&) = default;
        LuaSandbox& operator=(const LuaSandbox&) = default;
        LuaSandbox& operator=(LuaSandbox&&) = default;

        LuaRef loadScript(const std::string& path);

        void addGlobal(const std::string& name, std::function<int(void*)> fn);
        void removeGlobal(const std::string& name);

    private:
        LuaStack* m_stack;
        LuaRef m_environmentRef;
        std::map<std::string, std::unique_ptr<std::function<int(void*)>>> m_functions;
    };
}