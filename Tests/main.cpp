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
    LuaWrapper::LuaRef test{ sandbox.loadScript(std::string(LUA_TEST_BINARY) + "/Assets/test.lua") };
    EXPECT_TRUE(test.getFunction("test").call());
    EXPECT_TRUE(test.getFunction("delta").call(0.1f));
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
    LuaWrapper::LuaRef test{ sandbox.loadScript(std::string(LUA_TEST_BINARY) + "/Assets/testGlobal.lua") };

    EXPECT_TRUE(test.getFunction("callCPPFunction").call());

    sandbox.removeGlobal("testPrint");
}