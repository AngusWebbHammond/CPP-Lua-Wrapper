#pragma once

#include <string>

namespace LuaWrapper {
    class LuaStack;
    class LuaFunction;

    class LuaRef {
    public:
        LuaRef() = default;
        LuaRef(LuaStack* stack, int index);
        ~LuaRef();

        LuaRef(LuaRef&&) noexcept;
        LuaRef& operator=(LuaRef&&) noexcept;

        void push() const;
        bool valid() const { return m_ref != -1; }

        LuaFunction getFunction(const std::string& name);

    private:
        LuaStack* m_stack;
        int m_ref;
    };
}