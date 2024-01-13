if(NOT EXISTS ${pybind11_INSTALL_DIR})
    execute_process(COMMAND mkdir ${pybind11_INSTALL_DIR})
endif()

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
            -G ${CMAKE_GENERATOR}
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

set(pybind11_DIR ${pybind11_CMake_DIR})

message(STATUS "Pybind11 configured, built and installed.")
