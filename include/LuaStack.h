#pragma once

#include <string>

struct lua_State;

namespace LuaWrapper {
    class LuaState;

    class LuaStack {
    public:
        explicit LuaStack(LuaState* state);
        LuaStack(const LuaStack&) = delete;
        LuaStack(LuaStack&&);
        LuaStack& operator=(const LuaStack&) = delete;
        LuaStack& operator=(LuaStack&&);

        auto push(int v) -> void;
        auto push(double v) -> void;
        auto push(bool v) -> void;
        auto push(const std::string& v) -> void;
        auto pushNil() -> void;

        auto getInt(int index) -> int;
        auto getDouble(int index) -> double;
        auto getBool(int index) -> bool;
        auto getString(int index) -> std::string;

        auto top() const -> int;
        auto setTop(int t) -> void;

        auto getNativeState() -> lua_State*;

        auto isStateValid() -> bool { return m_state; }

        class Guard
        {
        public:
            Guard(LuaStack* stack);
            ~Guard();
        private:
            LuaStack* m_stack;
            int m_top;
        };

    private:
        LuaState* m_state;
    };
}