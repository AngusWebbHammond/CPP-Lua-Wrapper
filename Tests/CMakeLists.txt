if (BUILD_LUA_TESTS) 
    enable_testing()

    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    
    add_executable(lua_wrapper_tests main.cpp)
    
    target_link_libraries(lua_wrapper_tests
        PRIVATE
        lua_wrapper
        GTest::gtest_main
    )

    target_compile_definitions(lua_wrapper_tests PRIVATE LUA_TEST_BINARY="${CMAKE_CURRENT_BINARY_DIR}")

    include(GoogleTest)
    gtest_discover_tests(lua_wrapper_tests)

    add_custom_command(
        TARGET lua_wrapper_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/Assets
            ${CMAKE_CURRENT_BINARY_DIR}/Assets
    )
endif()