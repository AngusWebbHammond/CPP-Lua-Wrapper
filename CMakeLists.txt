cmake_minimum_required(VERSION 3.28)

project(lua_wrapper
    VERSION 1.0.0
    DESCRIPTION "Thin C++23 Lua wrapper"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(Vendors/lua-5.5.0)
add_subdirectory(Tests)

add_library(lua_wrapper STATIC)

target_sources(lua_wrapper PRIVATE 
    src/LuaRef.cpp
    src/LuaSandbox.cpp
    src/LuaStack.cpp
    src/LuaState.cpp
)

target_include_directories(lua_wrapper
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(lua_wrapper
    PUBLIC lua_static
)

add_library(lua_wrapper::lua_wrapper ALIAS lua_wrapper)