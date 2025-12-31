# Collect test source files
file(GLOB TEST_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp"
)

# Collect main project sources (excluding main.cpp)
file(GLOB_RECURSE PROJECT_SOURCES 
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)
list(FILTER PROJECT_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

# Create test executable
add_executable(run_tests ${TEST_SOURCES} ${PROJECT_SOURCES})

# Include directories
target_include_directories(run_tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/world
    ${CMAKE_SOURCE_DIR}/src/engine
    ${CMAKE_SOURCE_DIR}/src/player
    ${CMAKE_SOURCE_DIR}/src/raycasting
    ${CMAKE_SOURCE_DIR}/src/render
    ${CMAKE_SOURCE_DIR}/src/utils
    ${CMAKE_SOURCE_DIR}/src/input
)

# Link Google Test
target_link_libraries(run_tests PRIVATE 
    gtest 
    gtest_main
    m
)

# Discover tests
include(GoogleTest)
gtest_discover_tests(run_tests)
