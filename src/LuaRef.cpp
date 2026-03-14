#include "LuaRef.h"

#include <lua.hpp>

#include "LuaState.h"
#include "LuaStack.h"
#include "LuaFunction.h"
#include "LuaUtils.h"

namespace LuaWrapper {
    LuaRef::LuaRef(LuaStack* stack, int index)
        : m_stack(stack), m_ref(-1)
    {
        auto* state{ m_stack->getNativeState() };
        lua_pushvalue(state, index);
        m_ref = luaL_ref(state, LUA_REGISTRYINDEX);
    }

    LuaRef::~LuaRef()
    {
        if (m_ref != -1) {
            if (m_stack->isStateValid()) {
                luaL_unref(m_stack->getNativeState(), LUA_REGISTRYINDEX, m_ref);
            }
        }
    }

    LuaRef::LuaRef(const LuaRef& other) noexcept
        : m_stack(other.m_stack), m_ref(other.m_ref)
    {
    }

    LuaRef& LuaRef::operator=(const LuaRef& other) noexcept
    {
        m_stack = other.m_stack;
        m_ref = other.m_ref;

        return *this;
    }

    LuaRef::LuaRef(LuaRef&& other) noexcept
        : m_stack(other.m_stack), m_ref(other.m_ref)
    {
        other.m_stack = nullptr;
        other.m_ref = -1;
    }

    LuaRef& LuaRef::operator=(LuaRef&& other) noexcept
    {
        m_stack = other.m_stack;
        m_ref = other.m_ref;

        other.m_stack = nullptr;
        other.m_ref = -1;

        return *this;
    }

    void LuaRef::push() const
    {
        lua_rawgeti(m_stack->getNativeState(), LUA_REGISTRYINDEX, m_ref);
    }

    LuaFunction LuaRef::getFunction(const std::string& name)
    {
        LuaStack::Guard guard{ m_stack };
        push();
        lua_getfield(m_stack->getNativeState(), -1, name.c_str());
        return LuaFunction(m_stack, -1);
    }

}