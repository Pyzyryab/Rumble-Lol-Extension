# ----------------------------------------------------------------------------
#  ROOT CMake file for configure and build the project
#
#  Find more details on the README.md of the project
#
#  Zero Day Code, 2023
#
#  Usage instructions:
#   - move your pwd to the build directory, located in the root
#     (create one if not exists)
#   - launch: `cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=./clang-x86_64_windows_gnu.cmake ..`
#   - if everything was configured correctly, now build the project: cmake --build .
#  
#  Contributors:
#   -  Alex Vergara (@Pyzyrab)
# ----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.5)

set(PROJECT rumble_lol_plugin)

project(${PROJECT}
    VERSION 1.0.0
    DESCRIPTION "Rumble League Plugin, a Python Module extension for Rumble-AI"
    HOMEPAGE_URL "https://github.com/zerodaycode/Rumble-LoL-Plugin"
    LANGUAGES CXX
)

# CMake Debug mode by default 
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

list(APPEND CMAKE_CXX_FLAGS "-O2")
list(APPEND CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS} "-O3")

# require C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------- Project variables -------
set(RLP_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(RLP_CODE_ROOT ${RLP_ROOT}/code)

set(RLP_INCLUDE_DIR ${RLP_CODE_ROOT})
set(RLP_SOURCES_ROOT ${RLP_CODE_ROOT}/${PROJECT})

set(PROJECT_BUILD_DIRECTORY     ${RLP_ROOT}/build)
set(PROJECT_INSTALL_DIRECTORY   ${RLP_ROOT}/install)
# ------- Project variables -------

# Changing where CMake will performn the installations
set(CMAKE_INSTALL_PREFIX ${PROJECT_INSTALL_DIRECTORY})

# The toolchain file that will be used later to pass our project configuration also to the OpenCV build
set(CMAKE_TOOLCHAIN_FILE ${RLP_ROOT}/clang-x86_64_windows_gnu.cmake)

# Set the installation directory
set(OpenCV_INSTALL_DIR ${PROJECT_INSTALL_DIRECTORY}/opencv)
# Set the OpenCV build dir
set(OpenCV_BUILD_DIR ${PROJECT_BUILD_DIRECTORY}/opencv/build)
# Set the OpenCV_DIR, required to found the installation
set(OpenCV_DIR ${OpenCV_INSTALL_DIR})

# Attempt to find OpenCV in quiet mode. This will allow us to skip CMake code 
# in the consecutive iterations of the build process
find_package(OpenCV QUIET)

# Autogenerating the installation directories
if(NOT EXISTS ${PROJECT_INSTALL_DIRECTORY})
    execute_process(COMMAND mkdir ${PROJECT_INSTALL_DIRECTORY})
    message(STATUS "install folder created")
endif()

if(NOT EXISTS ${OpenCV_INSTALL_DIR})
    execute_process(COMMAND mkdir ${OpenCV_INSTALL_DIR})
endif()


# Check if OpenCV was found
if(OpenCV_FOUND)
    message(STATUS "OpenCV found. Version: ${OpenCV_VERSION}")
else()
    message(WARNING "OpenCV not found. Cloning the project, building it and installing it")
endif()

if(NOT OPENCV_FOUND)
    # Download and extract OpenCV sources
    message(STATUS "Downloading from GitHub OpenCV")
    execute_process(
        COMMAND git clone --branch 4.6.0 --single-branch https://github.com/opencv/opencv.git
        WORKING_DIRECTORY ${PROJECT_BUILD_DIRECTORY}
    )
    execute_process(COMMAND mkdir ${OpenCV_BUILD_DIR})

    # Configure the later build of OpenCV
    message(STATUS "Configuring the build and installation of OpenCV")
    execute_process(
        COMMAND cmake -G "Ninja"
                    -DCMAKE_INSTALL_PREFIX=${OpenCV_INSTALL_DIR}
                    -DBUILD_TESTS=OFF
                    -DBUILD_PERF_TESTS=OFF
                    -DBUILD_EXAMPLES=OFF
                    -DBUILD_opencv_apps=OFF
                    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                    -DWITH_ADE=OFF
                    -Wno-dev
                    -S ${CMAKE_CURRENT_SOURCE_DIR}/build/opencv
                    -B ${OpenCV_BUILD_DIR}
                    WORKING_DIRECTORY ${RLP_ROOT}
    )

    # Build and install OpenCV using execute_process
    message(STATUS "Building and installing OpenCV")
    execute_process(
        COMMAND cmake --build . --target install
        WORKING_DIRECTORY ${OpenCV_BUILD_DIR}
    )
else()
    message (STATUS "OpenCV installation found. Version: ${OpenCV_VERSION}. Path: ${OpenCV_DIR}")
endif()

# Find the OpenCV build/installation, so their own variables for the include/link are correctly set up
find_package(OpenCV REQUIRED)

# A little bit of debug information about the OpenCV installation 
message(STATUS "OpenCV_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS ${OpenCV_LIBS}")
message(STATUS "OpenCV build and installation finished. Launching the build of the example project")

# # Set the directory where Pybind11 will be downloaded
set(PYBIND11_DOWNLOAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/pybind11)
# Set the directory where Pybind11 will be installed
set(PYBIND11_INSTALL_DIR ${CMAKE_BINARY_DIR}/pybind11_install)


# Download and include Pybind11
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include/pybind11)
    message(STATUS "Downloading Pybind11...")
    file(DOWNLOAD https://github.com/pybind/pybind11/archive/v2.11.1.zip ${CMAKE_CURRENT_SOURCE_DIR}/pybind11.zip)
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_CURRENT_SOURCE_DIR}/pybind11.zip WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
    file(RENAME ${CMAKE_CURRENT_SOURCE_DIR}/include/pybind11-2.11.1 ${CMAKE_CURRENT_SOURCE_DIR}/include/pybind11)
    file(REMOVE ${CMAKE_CURRENT_SOURCE_DIR}/pybind11.zip)
    message(STATUS "Pybind11 downloaded and extracted.")
    # Build and install Pybind11
    execute_process(
        COMMAND ${CMAKE_COMMAND}
                --build ${CMAKE_CURRENT_SOURCE_DIR}/include/pybind11
                --target install
                -DCMAKE_POLICY_DEFAULT_CMP0148=OLD
                -DCMAKE_BUILD_TYPE=Release
                -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
                -DPYBIND11_TEST=OFF
                -Wno-dev
    )

    message(INFO " Pybind11 built and installed. Proceding to build RLP!")
else()
    message(INFO " Pybind11 is already installed. Proceding to build RLP!")
endif()


# Add the project's source files
set(SOURCES
    ${RLP_SOURCES_ROOT}/RumbleLeague.cpp
    ${RLP_SOURCES_ROOT}/league_client/screen.cpp
    ${RLP_SOURCES_ROOT}/motion/motion.cpp
    ${RLP_SOURCES_ROOT}/vision/vision.cpp
    ${RLP_SOURCES_ROOT}/capture/window_capture.cpp
    ${RLP_SOURCES_ROOT}/helpers/string.cpp
    ${RLP_SOURCES_ROOT}/ffi/pybind_conf.cpp
)


# find_package(pybind11 REQUIRED)
add_subdirectory(${PYBIND11_DOWNLOAD_DIR})
# pybind11_add_module(rumble_lol_plugin ${RLP_CODE_ROOT}/ffi/pybind_conf.cpp)

# Build the Python module
add_library(rumble_lol_plugin MODULE ${SOURCES})
# Wait for OpenCV to be built before proceeding
# add_dependencies(rumble_lol_plugin opencv_core opencv_imgproc)
target_include_directories(rumble_lol_plugin PRIVATE
    ${RLP_INCLUDE_DIR}
    ${OpenCV_INCLUDE_DIRS}
    
    ${Python_INCLUDE_DIRS}
    ${PYBIND11_DOWNLOAD_DIR}/src/pybind11/include
)


# target_link_directories(rumble_lol_plugin PRIVATE ${OpenCV_LIBRARY_DIRS})
# Link libraries
target_link_libraries(rumble_lol_plugin PUBLIC
    ${OpenCV_LIBS}
    
    pybind11::module
    pybind11::windows_extras
    ${Python_LIBRARIES}
)


pybind11_extension(rumble_lol_plugin)
if(NOT MSVC AND NOT ${CMAKE_BUILD_TYPE} MATCHES Debug|RelWithDebInfo)
    # Strip unnecessary sections of the binary on Linux/macOS
    pybind11_strip(example)
endif()

# Specify the output directory for the Python module
set_target_properties(rumble_lol_plugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)


# # Make sure to link against Python library
target_link_libraries(rumble_lol_plugin PRIVATE ${Python_LIBRARIES})
