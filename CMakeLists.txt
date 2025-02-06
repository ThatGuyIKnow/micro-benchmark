cmake_minimum_required(VERSION 3.10)
project(TreeCompression)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Function to download and prepare external repositories
function(clone_if_not_exists repo_url dest_dir git_tag)
    if(NOT EXISTS ${dest_dir})
        execute_process(COMMAND git clone ${repo_url} ${dest_dir})
        execute_process(COMMAND git checkout ${git_tag} WORKING_DIRECTORY ${dest_dir})
    endif()
endfunction()

# Set directories and commit hashes
set(BENCHMARK_DIR ${CMAKE_SOURCE_DIR}/benchmark)
set(BENCHMARK_GIT_REPO "https://github.com/google/benchmark.git")
set(BENCHMARK_GIT_TAG "2e16afc3fd53586f9949aa347c4bb909d15523a5")

set(GOOGLETEST_DIR ${BENCHMARK_DIR}/googletest)
set(GOOGLETEST_GIT_REPO "https://github.com/google/googletest.git")
set(GOOGLETEST_GIT_TAG "e235eb34c6c4fed790ccdad4b16394301360dcd4")

# Clone Benchmark and GoogleTest if they do not exist
clone_if_not_exists(${BENCHMARK_GIT_REPO} ${BENCHMARK_DIR} ${BENCHMARK_GIT_TAG})
clone_if_not_exists(${GOOGLETEST_GIT_REPO} ${GOOGLETEST_DIR} ${GOOGLETEST_GIT_TAG})

# Add Benchmark and GoogleTest
add_subdirectory(benchmark)

# Define source files
#set(SOURCES
#    tree_compression.cc
#)

set(SOURCE_FILE "tree_compression.cc" CACHE STRING "Single source file to run")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCE_FILE})

# Link benchmark library
target_link_libraries(${PROJECT_NAME} benchmark::benchmark)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug, Release, RelWithDebInfo, MinSizeRel)" FORCE)
endif()

# Set compiler flags
add_compile_options(-Wall -Wextra)

# Use configuration-specific flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Optional: Print the flags to verify they're set correctly
message(STATUS "Debug Flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "Release Flags: ${CMAKE_CXX_FLAGS_RELEASE}")
