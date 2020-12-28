cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_COVERAGE "Build coverage" OFF)

set(
        HUNTER_CACHE_SERVERS
        "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
        CACHE STRING "Default cache server"
)

include("cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.278.tar.gz"
        SHA1 "35fa55bc1dfcf9f4d7264f8bb26cd1759ce1ae07"
)


project(exp)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")
string(APPEND CMAKE_CXX_FLAGS " -lgcov --coverage")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

hunter_add_package(Boost COMPONENTS filesystem)
find_package(Boost CONFIG REQUIRED filesystem)


add_library(analysis STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/Analysis.cpp
        )

target_link_libraries(analysis Boost::filesystem)

target_include_directories(analysis
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

add_executable(main
        demo/main.cpp
        )

target_link_libraries(main analysis)

add_executable(tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
        )

target_link_libraries(tests GTest::gtest_main analysis)

enable_testing()
add_test(NAME unit_tests COMMAND tests)

if(BUILD_COVERAGE)
  set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/coverage/cmake")
  find_package(codecov)

  add_coverage(analysis)
  add_coverage(tests)
  coverage_evaluate()
endif()