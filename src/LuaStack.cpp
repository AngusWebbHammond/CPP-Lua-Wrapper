#include "LuaStack.h"

#include <lua.hpp>

#include "LuaState.h"
#include "LuaUtils.h"

namespace LuaWrapper {
    LuaStack::LuaStack(LuaState* state)
        : m_state{ state } {
    }

    auto LuaStack::push(int v) -> void
    {
        lua_pushinteger(toLua(m_state->getNativeState()), v);
    }

    auto LuaStack::push(double v) -> void
    {
        lua_pushnumber(toLua(m_state->getNativeState()), v);
    }

    auto LuaStack::push(bool v) -> void
    {
        lua_pushboolean(toLua(m_state->getNativeState()), v);
    }

    auto LuaStack::push(const std::string& v) -> void
    {
        lua_pushlstring(toLua(m_state->getNativeState()), v.c_str(), v.size());
    }

    auto LuaStack::pushNil() -> void
    {
        lua_pushnil(toLua(m_state->getNativeState()));
    }

    auto LuaStack::getInt(int index) -> int
    {
        return static_cast<int>(luaL_checkinteger(toLua(m_state->getNativeState()), index));
    }

    auto LuaStack::getDouble(int index) -> double
    {
        return luaL_checknumber(toLua(m_state->getNativeState()), index);
    }

    auto LuaStack::getBool(int index) -> bool
    {
        return lua_toboolean(toLua(m_state->getNativeState()), index) != 0;
    }

    auto LuaStack::getString(int index) -> std::string
    {
        return luaL_checkstring(toLua(m_state->getNativeState()), index);
    }

    auto LuaStack::top() const -> int
    {
        return lua_gettop(toLua(m_state->getNativeState()));
    }

    auto LuaStack::setTop(int t) -> void
    {
        lua_settop(toLua(m_state->getNativeState()), t);
    }

    auto LuaStack::getNativeState() -> lua_State*
    {
        return toLua(m_state->getNativeState());
    }

    LuaStack::Guard::Guard(LuaStack* stack)
        : m_stack{ stack }, m_top{ m_stack->top() }
    {
    }

    LuaStack::Guard::~Guard()
    {
        m_stack->setTop(m_top);
    }

}