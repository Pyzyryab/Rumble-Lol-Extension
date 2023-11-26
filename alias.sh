#!/bin/sh

# This file provides command alias to make easy the workflow within the development of this project
# Note that the alias are ready to be executed from within the root path of the project

# Build the RLE with setup-tools
alias build='pip install ./python_mod/c++_bindings'

# Clean the build project and uninstall RLE from the global or the active venv
alias clean='rm -rf ./python_mod/c++_bindings/build && ./python_mod/c++_bindings/Rumble_LoL_Plugin.egg-info && pip uninstall Rumble-LoL-Plugin'

# Run the RLE plugin
alias run='python ./python_mod/run_rlp.py'

# Cleans first, then launches the build process
alias cleanbuild='clean && build'

# Cleans first, builds the project and then launches the RLE
alias cbr='clean && build && run'