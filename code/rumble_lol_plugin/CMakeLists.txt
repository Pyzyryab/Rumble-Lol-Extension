# ----------------------------------------------------------------------------
#  CMake file for the source code files of the project
#
#  Find more details on the README.md of the project
#
#  Zero Day Code, 2023 - Present
# ----------------------------------------------------------------------------

# Declares the project's source files
set(SOURCES
    ${RLP_SOURCES_ROOT}/RumbleLeague.cpp
    ${RLP_SOURCES_ROOT}/ffi/rlp.cpp
    ${RLP_SOURCES_ROOT}/league_client/screen.cpp
    ${RLP_SOURCES_ROOT}/motion/motion.cpp
    ${RLP_SOURCES_ROOT}/vision/vision.cpp
    ${RLP_SOURCES_ROOT}/capture/window_capture.cpp
    ${RLP_SOURCES_ROOT}/helpers/string.cpp
)

# Find `pybind11`
find_package(pybind11 CONFIG REQUIRED)

# Create our CMake target
pybind11_add_module(${PY_MODULE} MODULE ${SOURCES})

# Specify the headers to be included
target_include_directories(${PY_MODULE} PRIVATE
    ${RLP_INCLUDE_DIR}
    ${OpenCV_INCLUDE_DIRS}
    ${pybind11_INSTALL_DIR}/include
    ${Python_LIBRARIES}
)

# Link libraries to our generated Python module
target_link_libraries(${PY_MODULE} PUBLIC
    ${OpenCV_LIBS}
    pybind11::module
    pybind11::lto
    pybind11::thin_lto
)

# Specify the output directory for the Python module
set_target_properties(${PY_MODULE} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARIES_DIRECTORY}
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARIES_DIRECTORY}
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARIES_DIRECTORY}
)

# Manually setting the correct module extension. When loaded, it requires to have a concrete
# extension suffix in order to be correctly used by the project
set_target_properties(${PY_MODULE} PROPERTIES PREFIX "" SUFFIX ".cp311-mingw_x86_64_clang.pyd")
