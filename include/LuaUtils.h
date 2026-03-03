#pragma once

struct lua_State;

namespace LuaWrapper {
    static lua_State* toLua(void* s) {
        return static_cast<lua_State*>(s);
    }
}