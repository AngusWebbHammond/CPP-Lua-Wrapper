#include <gtest/gtest.h>

#include <print>

#include "LuaState.h"
#include "LuaSandbox.h"
#include "LuaRef.h"
#include "LuaFunction.h"
#include "LuaUtils.h"
#include "LuaStack.h"

// TODO build more tests for this Lua Wrapper

TEST(LuaTests, LuaFileTest) {
    LuaWrapper::LuaState state{};
    auto sandbox{ state.createSandbox() };
    LuaWrapper::LuaRef test{ sandbox.loadScript("Tests/test.lua") };
    test.getFunction("test").call();
    test.getFunction("delta").call(0.1f);
    EXPECT_TRUE(test.valid());
}

void testPrint(int i) {
    std::println("Test with input: {}", i);
}

TEST(LuaTests, LuaCallbackTest) {
    LuaWrapper::LuaState state{};

    auto sandbox{ state.createSandbox() };
    sandbox.addGlobal("testPrint", [&state](void* s) -> int
        {
            LuaWrapper::LuaStack stack(&state);
            int value{ stack.getInt(1) };
            testPrint(value);
            return 0;
        }
    );

    LuaWrapper::LuaRef test{ sandbox.loadScript("Tests/testGlobal.lua") };
    test.getFunction("callCPPFunction").call();

    sandbox.removeGlobal("testPrint");
    EXPECT_TRUE(true);
}