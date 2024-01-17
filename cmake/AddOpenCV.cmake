
if(NOT EXISTS ${OpenCV_INSTALL_DIR})
    execute_process(COMMAND mkdir ${OpenCV_INSTALL_DIR})
endif()

# Download and extract OpenCV sources
message(STATUS "Downloading OpenCV from GitHub")
# TODO check if dir exists, so we can skip everything
# TODO or we plan to delete it, so check if its populated on install??
execute_process(
    COMMAND git clone --branch 4.6.0 --single-branch https://github.com/opencv/opencv.git
    WORKING_DIRECTORY ${PROJECT_BUILD_DIRECTORY}
)
execute_process(COMMAND mkdir ${OpenCV_BUILD_DIR})

# Configure the later build of OpenCV
message(STATUS "Configuring the build and installation of OpenCV")
execute_process(
    COMMAND ${CMAKE_COMMAND} 
        -G ${CMAKE_GENERATOR}
        -DCMAKE_INSTALL_PREFIX=${OpenCV_INSTALL_DIR}
        -DCMAKE_BUILD_TYPE=Release
        -DBUILD_TESTS=OFF
        -DBUILD_PERF_TESTS=OFF
        -DBUILD_EXAMPLES=OFF
        -DBUILD_opencv_apps=OFF
        -DBUILD_opencv_python2=OFF
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
        # TODO add the conf opts for reduce the number of OpenCV modules built
        -DWITH_ADE=OFF
        -DENABLE_PRECOMPILED_HEADERS=ON
        -DBUILD_LIST=core,imgproc,highgui,videoio
        # -DOPENCV_ALLOCATOR_STATS_COUNTER_TYPE=int/int64_t · TODO doesn't works with C++23
        -Wno-dev
        -S ${CMAKE_CURRENT_SOURCE_DIR}/build/opencv
        -B ${OpenCV_BUILD_DIR}
        WORKING_DIRECTORY ${RLP_ROOT}
)

# Build and install OpenCV
message(STATUS "Building and installing OpenCV")
execute_process(
    COMMAND cmake --build . --target install
    WORKING_DIRECTORY ${OpenCV_BUILD_DIR}
)

set(OpenCV_DIR ${OpenCV_CMake_DIR})
message(STATUS "OpenCV configured, built and installed.")

# A little bit of debug information about the OpenCV installation 
message(STATUS "OpenCV_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS ${OpenCV_LIBS}")
