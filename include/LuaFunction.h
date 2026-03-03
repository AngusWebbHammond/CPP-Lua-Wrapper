#pragma once

#include <lua.hpp>

#include <print>

#include "LuaStack.h"
#include "LuaRef.h"
#include "LuaUtils.h"

namespace LuaWrapper {
    class LuaFunction
    {
    public:
        LuaFunction(LuaStack* stack, int index)
            : m_stack(stack), m_ref(stack, index)
        {
        }

        template<typename... Args>
        void call(Args... args);

    private:
        LuaStack* m_stack;
        LuaRef m_ref;
    };

    template<typename ...Args>
    inline void LuaFunction::call(Args ...args)
    {
        auto state{ toLua(m_stack->getNativeState()->getNativeState()) };
        LuaStack::Guard guard{ m_stack };

        m_ref.push();
        (m_stack->push(args), ...);

        if (lua_pcall(state, sizeof...(Args), 0, 0) != LUA_OK) {
            std::println("Lua Error: {}", lua_tostring(state, -1));
        }
    }

}