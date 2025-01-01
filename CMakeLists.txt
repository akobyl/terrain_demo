cmake_minimum_required(VERSION 3.28)
cmake_policy(SET CMP0074 NEW)
project(TerrainDemo LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(FetchContent)

FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 3.0.0
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
  box2d
  GIT_REPOSITORY https://github.com/erincatto/box2d.git
  GIT_TAG v3.0.0
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM)
FetchContent_MakeAvailable(box2d)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM
)
FetchContent_MakeAvailable(googletest)

# Add source files
add_executable(TerrainDemo
  src/main.cpp
  src/physics_hex.cpp
  src/physics_ball.cpp
)

target_link_libraries(TerrainDemo PRIVATE
  SFML::Graphics
  box2d
)

# Google Testing
enable_testing()

add_executable(
  TerrainDemoTest
  test/test_main.cpp
  src/physics_hex.cpp
  src/physics_ball.cpp
)

target_link_libraries(
  TerrainDemoTest
  GTest::gtest_main
  SFML::Graphics
  box2d
)

target_include_directories(TerrainDemoTest PRIVATE
  ${CMAKE_SOURCE_DIR}/src
)

include(GoogleTest)
gtest_discover_tests(TerrainDemoTest)
