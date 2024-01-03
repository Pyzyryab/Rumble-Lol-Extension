#!/bin/sh

# This file provides command alias to make easy the workflow within the development of this project
# Note that the alias are ready to be executed from within the root path of the project

# Build the RLE with setup-tools
alias build='pip install ./python/c++_bindings'

# Clean the build project and uninstall RLE from the global or the active venv
alias clean='rm -rf ./python/c++_bindings/build && rm -rf ./python/c++_bindings/Rumble_LoL_Plugin.egg-info && pip uninstall Rumble-LoL-Plugin'

# Run the RLE plugin
alias run='python ./python/run_rlp.py'

# Cleans first, then launches the build process
alias cleanbuild='clean && build'

# Cleans first, builds the project and then launches the RLE
alias cbr='clean && build && run'

## NEW ONES, intended to be used with the CMake pipeline
alias clean_cmake='rm -rf build && rm -rf include/pybind11 && mkdir build'
alias configure_cmake='(cd build && cmake -G "Ninja" -DCMAKE_CXX_COMPILER=C:/msys64/mingw64/bin/clang++.exe -DCMAKE_MAKE_PROGRAM=C:/msys64/usr/bin/make.exe -DCMAKE_AR=C:/msys64/mingw64/bin/ar.exe ..) || cd ..'
alias run_make='(cd build && C:/msys64/usr/bin/make.exe) || cd ..'

alias first_build='mkdir build && configure_cmake && run_make'
alias build='configure_cmake && run_make'
alias clean_rebuild='clean_cmake && configure_cmake && run_make'
