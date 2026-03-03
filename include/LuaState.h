#pragma once

#include <memory>

namespace LuaWrapper {
    class LuaStack;
    class LuaSandbox;

    class LuaState {
    public:
        LuaState();
        ~LuaState();

        LuaStack& getStack();
        LuaSandbox createSandbox();

    private:
        struct Impl;

        Impl createImpl();
        void destroyImpl();

        std::unique_ptr<Impl> m_impl;

        void* getNativeState() const;

        friend class LuaStack;
        friend class LuaRef;
        friend class LuaSandbox;
        friend class LuaFunction;
    };
}