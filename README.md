# Lightweight Lua Wrapper

I have built this Lua Wrapper as a library to include in a game engine I am building as the scripting engine, the main aim was to remove the need for any Lua specific calls within the engine.
This has only been tested on windows with the MSVC 2022 compiler.
If you find any issues please raise them, or open a pull request for review in a branch.

This project is licensed under the MIT License, see [LICENSE](/LICENSE).

## Dependencies

- [GoogleTest](https://github.com/google/googletest) - Google's Testing suite
- [Lua](https://www.lua.org/) - The c files for Lua, these have been included in the project.

## How to build

It is recommended to build this through CMake as a static library. To build:

```sh
    cmake -S . -B build
    cmake --build build --config Debug
```

If you are looking to include this as a static library, then you should be aware of the following options, if you want to disable testing, then you should set `BUILD_LUA_TESTS` to off in your CMake configuration files.

## Running the tests

Once built, the unit tests can be executed from the build directory:

```sh
    .\build\Tests\Debug\lua_wrapper_tests.exe
```

To see the test files, look in the `/Tests` directory.

## Usage

The wrapper is intended to provide a thin, type-safe C++ interface on top of the Lua C API. Example usage:

```c++
    #include "LuaState.h"
    #include "LuaStack.h"
    #include "LuaSandbox.h"

    int main() {
        LuaWrapper::LuaState state{};
        auto sandbox{ state.createSandbox() };
        LuaWrapper::LuaRef test{ sandbox.loadScript("Tests/test.lua") };
        test.getFunction("test").call();
        test.getFunction("delta").call(0.1f);
    }
```

The test file for this above code is the following, located at [test.lua](/Tests/test.lua):

```lua
    local Test = {}

    function Test.test()
        print("Test Called")
    end

    function Test.delta(dt)
        print("Delta Called with time: ", dt)
    end

    return Test
```

Refer to the header files in `/include` for more documentation and examples.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
