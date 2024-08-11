cmake_minimum_required(VERSION 3.22)

project(
    brabham
    VERSION 0.1.0
)

# check mandatory configuration
if(NOT (TORCS_BASE))
    message(FATAL_ERROR "Base source directory TORCS_BASE not defined")
else()
    cmake_path(APPEND TORCS_EXPORTS_INCLUDE_DIR "${TORCS_BASE}" "export" "include")
    cmake_path(APPEND TORCS_EXPORTS_LIB_DIR "${TORCS_BASE}" "export" "lib")
    cmake_path(APPEND TORCS_LIBS_INCLUDE_DIR "${TORCS_BASE}" "src" "libs")
    cmake_path(APPEND TORCS_INTERFACES_INCLUDE_DIR "${TORCS_BASE}" "src" "interfaces")
    cmake_path(APPEND TORCS_TEXTURES_DATA_DIR "${TORCS_BASE}" "data" "data" "textures")
    cmake_path(APPEND TORCS_CARS_DATA_DIR "${TORCS_BASE}" "data" "cars" "models")
endif()
if(NOT (TORCS_PREFIX))
    message(FATAL_ERROR "Installation directory TORCS_PREFIX not defined")
else()
    cmake_path(APPEND TORCS_LIB_DIR "${TORCS_PREFIX}" "lib" "torcs")
    cmake_path(APPEND TORCS_DATA_DIR "${TORCS_PREFIX}" "share" "games" "torcs")
    cmake_path(APPEND TORCS_DRIVER_LIB_DIR "${TORCS_LIB_DIR}" "drivers" ${PROJECT_NAME})
    cmake_path(APPEND TORCS_DRIVER_DATA_DIR "${TORCS_DATA_DIR}" "drivers" ${PROJECT_NAME})
endif()

# check mandatory dependencies
find_library(OPEN_AL_LIBRARY NAMES openal)
find_library(AL_UTILITY_TOOLKIT_LIBRARY NAMES alut)
find_library(VORBIS_FILE_LIBRARY NAMES vorbisfile)


# specify compiler features for all targets
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-Wall -fno-strict-aliasing -O2 -g)
endif()


# process the source directory
cmake_path(APPEND SRC_CMAKE_FILE "${CMAKE_SOURCE_DIR}" "src" "CMakeLists.txt")
include("${SRC_CMAKE_FILE}")
