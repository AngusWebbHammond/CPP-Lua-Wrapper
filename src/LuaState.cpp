#include "LuaState.h"

#include <lua.hpp>

#include "LuaStack.h"
#include "LuaSandbox.h"

namespace LuaWrapper {
    struct LuaState::Impl {
        lua_State* state{ nullptr };
        std::unique_ptr<LuaStack> stack{ nullptr };
    };

    LuaState::Impl LuaState::createImpl()
    {
        LuaState::Impl impl{
            .state{luaL_newstate()},
            .stack{std::make_unique<LuaStack>(this)}
        };
        luaL_openlibs(impl.state);
        return impl;
    }

    void LuaState::destroyImpl()
    {
        lua_close(m_impl->state);
    }

    LuaState::LuaState()
        : m_impl{ std::make_unique<Impl>(createImpl()) } {
    }

    LuaState::~LuaState()
    {
        destroyImpl();
    }

    LuaStack& LuaState::getStack()
    {
        return *m_impl->stack;
    }

    LuaSandbox LuaState::createSandbox()
    {
        return LuaSandbox{ m_impl->stack.get() };
    }

    void* LuaState::getNativeState() const
    {
        return m_impl->state;
    }

}