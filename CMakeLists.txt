# ----------------------------------------------------------------------------
#  ROOT CMake file for configure and build the project
#
#  Find more details on the README.md of the project
#
#  Zero Day Code, 2023 - Present
#
#  Usage instructions:
#   - move your pwd to the build directory, located in the root
#     (create one if not exists)
#   - launch: `cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=./clang-x86_64_windows_gnu.cmake ..`
#   - if everything was configured correctly, now build the project: cmake --build .
#
#   - You can also use a fancy one-line for build and configure, and also you can do it from
#     the project's root, like this:
#     `cmake -S . -B ./build -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=./clang-x86_64_windows_gnu.cmake && cmake --build ./build`
#
#   - Anyway, instead of manually be launching the commands, you should be using `make`, which
#     is ready to work out-of-the-box. Read the `Makefile` located at the root of the project
#     to acknowledge what targets are available
#
#  Contributors:
#   - Alex Vergara (@Pyzyrab)
#   - Pylyv        (@Pylyv)
# ----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.5)

set(PROJECT rumble_lol_plugin)
set(PY_MODULE rlp)

project(${PROJECT}
    VERSION 0.1.0
    DESCRIPTION "Rumble League Plugin, a Python Module extension for Rumble-AI"
    HOMEPAGE_URL "https://github.com/zerodaycode/Rumble-LoL-Plugin"
    LANGUAGES CXX
)

# Generate timestamp
string(TIMESTAMP BUILD_TIMESTAMP "%Y-%m-%dT%H:%M:%SZ")

# Exporting the compiler generated commands for IDEs and static analysis tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# CMake Debug mode by default 
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# TODO add the project's CXX flags, like -Wall...

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")

# require C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------- Project variables -------
set(RLP_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(RLP_CODE_ROOT ${RLP_ROOT}/code)

set(RLP_INCLUDE_DIR ${RLP_CODE_ROOT})
set(RLP_SOURCES_ROOT ${RLP_CODE_ROOT}/${PROJECT})

set(PROJECT_BUILD_DIRECTORY     ${RLP_ROOT}/build)
set(PROJECT_INSTALL_DIRECTORY   ${RLP_ROOT}/install)
set(PROJECT_BINARIES_DIRECTORY  ${RLP_ROOT}/bin)

# Changing where CMake will perform the installations
set(CMAKE_INSTALL_PREFIX ${PROJECT_INSTALL_DIRECTORY})

# The toolchain file that will be used later to pass our project configuration also to the OpenCV build
set(CMAKE_TOOLCHAIN_FILE ${RLP_ROOT}/clang-x86_64_windows_gnu.cmake)

# Adding the cmake helpers files
list(APPEND CMAKE_MODULE_PATH ${RLP_ROOT}/cmake)

# ------- 3rd party set ups -------
# Set the installation directory
set(OpenCV_INSTALL_DIR      ${PROJECT_INSTALL_DIRECTORY}/opencv)
set(pybind11_INSTALL_DIR    ${PROJECT_INSTALL_DIRECTORY}/pybind11)
# Let CMake to discover them with `FindPackage()`
set(OpenCV_CMake_DIR        ${OpenCV_INSTALL_DIR})
set(OpenCV_DIR              ${OpenCV_CMake_DIR})
set(pybind11_CMake_DIR      ${pybind11_INSTALL_DIR}/share/cmake/pybind11)
set(pybind11_DIR            ${pybind11_CMake_DIR})
# Set the build dirs
set(OpenCV_BUILD_DIR        ${PROJECT_BUILD_DIRECTORY}/opencv/build)
set(pybind11_BUILD_DIR      ${PROJECT_BUILD_DIRECTORY}/pybind11/build)

message(STATUS "")
message(STATUS "------------------------ RLP Project Configuration ------------------------")
message(STATUS "==================  General configuration for ${PROJECT} ==================")
message(STATUS "    Version control:               ${PROJECT_VERSION}")
message(STATUS "")
message(STATUS "    Platform:")
message(STATUS "      Timestamp:                   ${BUILD_TIMESTAMP}")
message(STATUS "      Host:                        ${CMAKE_HOST_SYSTEM_NAME} ${CMAKE_HOST_SYSTEM_VERSION} ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS "      CMake:                       ${CMAKE_VERSION}")
message(STATUS "      CMake generator:             ${CMAKE_GENERATOR}")
message(STATUS "      CMake build tool:            ${CMAKE_MAKE_PROGRAM}")
message(STATUS "      Build type:                  ${CMAKE_BUILD_TYPE}")
message(STATUS "")
message(STATUS "    C/C++:")
message(STATUS "      C++ standard:                ${CMAKE_CXX_STANDARD}")
message(STATUS "      C++ Compiler:                ${CMAKE_CXX_COMPILER} (ver ${CMAKE_CXX_COMPILER_VERSION})")
message(STATUS "      C++ flags (Release):         ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "      C++ flags (Debug):           ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "      Linker flags (Release):      ${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
message(STATUS "      Linker flags (Debug):        ${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
message(STATUS "")
message(STATUS "    Paths/DIRS configuration:")
message(STATUS "      Project's root:              ${RLP_ROOT}")
message(STATUS "      Source code root:            ${RLP_CODE_ROOT}")
message(STATUS "      Active toolchain file:       ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "      Our CMake modules are:       ${CMAKE_MODULE_PATH}")
message(STATUS "      Build directory:             ${PROJECT_BUILD_DIRECTORY}")
message(STATUS "      Dependencies install path:   ${PROJECT_INSTALL_DIRECTORY}")
message(STATUS "      CMake prefix path:           ${CMAKE_INSTALL_PREFIX}")
message(STATUS "      Binaries will be dumped to:  ${PROJECT_BINARIES_DIRECTORY}")
message(STATUS "")
message(STATUS "      OpenCV_DIR discover config:  ${OpenCV_DIR}")
message(STATUS "      OpenCV build dir:            ${OpenCV_BUILD_DIR}")
message(STATUS "      OpenCV install dir:          ${OpenCV_INSTALL_DIR}")
message(STATUS "      pybind11 discover config:    ${pybind11_DIR}")
message(STATUS "      pybind11 build dir:          ${pybind11_BUILD_DIR}")
message(STATUS "      pybind11 install dir:        ${pybind11_BUILD_DIR}")

message(STATUS "------------------------ End Project Configuration ------------------------")
message(STATUS "")

# add the project's configuration header
add_subdirectory(configuration)

# Autogenerating the installation directories
if(NOT EXISTS ${PROJECT_INSTALL_DIRECTORY})
    execute_process(COMMAND mkdir ${PROJECT_INSTALL_DIRECTORY})
    message(STATUS "install folder created")
endif()

# Ensuring that Python is present and is discovereable
find_package(Python COMPONENTS Interpreter Development REQUIRED)

message(STATUS "")
message(STATUS "==================  Handling dependencies ==================")

# Handle OpenCV
message(STATUS "------------------------ OpenCV ------------------------")
find_package(OpenCV QUIET)
if(OpenCV_FOUND)
    message(STATUS "OpenCV found. Version: ${OpenCV_VERSION}")
else()
    message (STATUS "OpenCV NOT found. Cloning the project, building it and installing it")
    include(AddOpenCV)
endif()

find_package(OpenCV REQUIRED)
message(STATUS "------------------------ End OpenCV ------------------------")
message(STATUS "")

message(STATUS "------------------------ pybind11 ------------------------")
find_package(pybind11 QUIET)
if(pybind11_FOUND)
    message(STATUS "pybind11 found. Version: ${pybind11_VERSION}")
else()
    message(WARNING "pybind11 not found. Cloning the project, building it and installing it")
    include(AddPybind11)
endif()
message(STATUS "------------------------ End pybind11 ------------------------")
message(STATUS "")

find_package(pybind11 REQUIRED)

message(STATUS "=============================================================")
message(STATUS "")

message(STATUS "==================  Configuring ${PROJECT} ==================")
# Brings the configuration of our main target, the C++ library that will
# be built as a Python module extension
add_subdirectory(code)
