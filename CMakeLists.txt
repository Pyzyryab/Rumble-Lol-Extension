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
set(OpenCV_DIR              ${OpenCV_INSTALL_DIR})
# Set the build dirs
set(OpenCV_BUILD_DIR        ${PROJECT_BUILD_DIRECTORY}/opencv/build)
set(pybind11_BUILD_DIR      ${PROJECT_BUILD_DIRECTORY}/pybind11/build)

# add the project's configuration header
add_subdirectory(configuration)

# Autogenerating the installation directories
if(NOT EXISTS ${PROJECT_INSTALL_DIRECTORY})
    execute_process(COMMAND mkdir ${PROJECT_INSTALL_DIRECTORY})
    message(STATUS "install folder created")
endif()

if(NOT EXISTS ${OpenCV_INSTALL_DIR})
    execute_process(COMMAND mkdir ${OpenCV_INSTALL_DIR})
endif()
if(NOT EXISTS ${pybind11_INSTALL_DIR})
    execute_process(COMMAND mkdir ${pybind11_INSTALL_DIR})
endif()

find_package(Python COMPONENTS Interpreter Development REQUIRED)

# Attempt to find OpenCV in quiet mode. This will allow us to skip CMake code 
# in the consecutive iterations of the build process
find_package(OpenCV QUIET)
if(OpenCV_FOUND)
    message(STATUS "OpenCV found before include. Version: ${OpenCV_VERSION}")
else()
    message (STATUS "OpenCV NOT found. Getting it")
    include(AddOpenCV)
endif()

# Find the OpenCV build/installation, so their own variables for the include/link are correctly set up
find_package(OpenCV REQUIRED)

# Check if pybind11 was found
if(pybind11_FOUND)
    message(STATUS "pybind11 found. Version: ${pybind11_VERSION}")
else()
    message(WARNING "pybind11 not found. Cloning the project, building it and installing it")
endif()


# Download and include pybind11
if(NOT pybind11_FOUND)
    # Download and extract OpenCV sources
    message(STATUS "Downloading pybind11 from GitHub")
    execute_process(
        COMMAND git clone --branch v2.11 --single-branch https://github.com/pybind/pybind11
        WORKING_DIRECTORY ${PROJECT_BUILD_DIRECTORY}
    )
    execute_process(COMMAND mkdir ${pybind11_BUILD_DIR})

    # Configure Pybind11
    message(STATUS "Configuring the installation of pybind11")
    execute_process(
        COMMAND ${CMAKE_COMMAND}
                -G "Ninja"
                -DCMAKE_INSTALL_PREFIX=${pybind11_INSTALL_DIR}
                -DCMAKE_POLICY_DEFAULT_CMP0148=OLD
                -DCMAKE_BUILD_TYPE=Release
                -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                -DPYBIND11_TEST=OFF
                -Wno-dev
                -S ${CMAKE_CURRENT_SOURCE_DIR}/build/pybind11
                -B ${pybind11_BUILD_DIR}
                WORKING_DIRECTORY ${RLP_ROOT}
    )

    # Build and install pybind11
    message(STATUS "Building and installing pybind11")
    execute_process(
        COMMAND ${CMAKE_COMMAND} --build . --target install
        WORKING_DIRECTORY ${pybind11_BUILD_DIR}
    )

    set(pybind11_DIR ${pybind11_INSTALL_DIR}/share/cmake/pybind11)

    message(INFO " Pybind11 configured, built and installed.")
else()
    message(INFO " Pybind11 is already configured, built and installed.")
endif()

# Brings the configuration of our main target, the C++ library that will
# be built as a Python module extension
add_subdirectory(code)
