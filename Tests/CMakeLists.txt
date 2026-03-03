option(BUILD_LUA_TESTS "Build Tests" ON)

if (BUILD_LUA_TESTS) 
    enable_testing()
    
    add_subdirectory(../Vendors/googletest ${CMAKE_BINARY_DIR}/googletest-build)

    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    
    add_executable(lua_wrapper_tests main.cpp)
    
    target_link_libraries(lua_wrapper_tests
        PRIVATE
        lua_wrapper
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(lua_wrapper_tests)
endif()