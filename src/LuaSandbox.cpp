#include "LuaSandbox.h"

#include <lua.hpp>

#include <print>

#include "LuaStack.h"
#include "LuaRef.h"
#include "LuaState.h"
#include "LuaUtils.h"

namespace LuaWrapper {
    LuaSandbox::LuaSandbox(LuaStack* stack)
        : m_stack{ stack }
    {
        auto* state{ m_stack->getNativeState() };
        LuaStack::Guard guard{ m_stack };

        lua_newtable(state);

        lua_pushcfunction(state, [](lua_State* s) -> int
            {
                int n = lua_gettop(s);
                for (int i{ 1 }; i <= n; i++) {
                    std::print("{}", lua_tostring(s, i));
                }
                std::println("");
                return 0;
            }
        );

        lua_setfield(state, -2, "print");

        m_environmentRef = LuaRef(m_stack, -1);
    }

    LuaRef LuaSandbox::loadScript(const std::string& path)
    {
        auto* state{ m_stack->getNativeState() };
        LuaStack::Guard guard{ m_stack };

        if (luaL_loadfile(state, path.c_str()) != LUA_OK) {
            return LuaRef(m_stack, -1);
        }

        m_environmentRef.push();
        lua_setupvalue(state, -2, 1);

        if (lua_pcall(state, 0, 1, 0) != LUA_OK) {
            return LuaRef(m_stack, -1);
        }

        return LuaRef(m_stack, -1);
    }

    void LuaSandbox::addGlobal(const std::string& name, std::function<int(void*)> fn)
    {
        auto* state{ m_stack->getNativeState() };
        LuaStack::Guard guard{ m_stack };

        m_functions.insert({ name, std::make_unique<std::function<int(void*)>>(fn) });

        m_environmentRef.push();
        lua_pushlightuserdata(state, m_functions.at(name).get());
        lua_pushcclosure(state, [](lua_State* s) -> int {
            auto* fn = static_cast<std::function<int(lua_State*)>*>(lua_touserdata(s, lua_upvalueindex(1)));
            return (*fn)(s);
            }, 1);
        lua_setfield(state, -2, name.c_str());
    }

    void LuaSandbox::removeGlobal(const std::string& name)
    {
        auto* state{ m_stack->getNativeState() };
        LuaStack::Guard guard{ m_stack };

        m_environmentRef.push();
        m_stack->pushNil();
        lua_setfield(state, -2, name.c_str());

        m_functions.erase(name);
    }

}
