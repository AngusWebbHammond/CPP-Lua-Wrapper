#pragma once

#include <string>

namespace LuaWrapper {
    class LuaState;

    class LuaStack {
    public:
        explicit LuaStack(LuaState* state);

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

        auto getNativeState() -> LuaState*;

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