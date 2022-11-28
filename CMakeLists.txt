cmake_minimum_required(VERSION 3.10)

project(final VERSION 0.1)

# Specify C++ compiler and linker
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_LINKER "/usr/bin/clang++")

# Specify C++ Standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify Debug build.
set(CMAKE_BUILD_TYPE Debug)

# Specify warnings for all builds.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function")

# Specify debug symbols and no optimizations for Debug builds.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG -O0 -gdwarf-4")

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES)

set(tests_dir ${CMAKE_SOURCE_DIR}/tests)
set(src_dir ${CMAKE_SOURCE_DIR}/src)

add_subdirectory(${tests_dir})
add_subdirectory(${src_dir})

add_executable(test ${tests_dir}/tests.cpp)
target_link_libraries(test PRIVATE tests)

add_executable(main ${src_dir}/main.cpp)
target_link_libraries(main PRIVATE src)