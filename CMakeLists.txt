cmake_minimum_required(VERSION 3.16)
project(mini_bundle VERSION "1.0.0")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# helper functions
include(cmake/dump_cmake_variables.cmake)
include(cmake/lg_cmake_utils.cmake)

###############################################################################
# mini_bundle 
###############################################################################
set(MINIBUNDLE_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "" FORCE)

include_directories("${MINIBUNDLE_PATH}")

include_directories("${MINIBUNDLE_PATH}/external/imgui")
include_directories("${MINIBUNDLE_PATH}/external/imgui/imgui")
include_directories("${MINIBUNDLE_PATH}/external/imgui/imgui/backends")

include_directories("${MINIBUNDLE_PATH}/external/implot")
include_directories("${MINIBUNDLE_PATH}/external/implot/implot")

set(MINI_BUNDLE_BUILD_PYTHON ON)
set(MINI_BUNDLE_BUILD_CPP   OFF)

option(MINI_BUNDLE_BUILD_DEMOS "Build mini_bundle C++ demos" OFF)

add_compile_definitions(MINI_BUNDLE_BUILD_PYTHON)
add_compile_definitions(MINI_BUNDLE_PYTHON_API)

set(MINI_BUNDLE_WITH_GLFW ON CACHE BOOL "" FORCE)

#########################################################################
# find pybind11
#########################################################################
include(cmake/find_pybind11.cmake)
find_pybind11()  # provided by cmake/find_pybind11.cmake

#########################################################################
# Main library (mini_bundle)
#########################################################################
file(GLOB mini_bundle_sources src/mini_bundle/*.cpp src/mini_bundle/*.h)
add_library(mini_bundle STATIC ${mini_bundle_sources})
target_include_directories(mini_bundle PUBLIC src)

#########################################################################
# Build external libraries: this will add imgui, implot, etc
#########################################################################
add_subdirectory(external)

#########################################################################
# Build python bindings
#########################################################################
include(cmake/lg_setup_module.cmake)
include(cmake/add_mini_bundle_bindings.cmake)
add_mini_bundle_bindings()

