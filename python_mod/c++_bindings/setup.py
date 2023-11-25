"""
Rumble LoL Extension

This is a Python package that extends the Rumble-AI project with a C++ module.

Usage (from the root directory):
    $ pip install ./python_mod/c++_bindings
"""

import os
import sys
import subprocess

try:
    import pybind11
except ImportError as err:
    if subprocess.call([sys.executable, '-m', 'pip', 'install', 'pybind11']):
        raise RuntimeError('pybind11 install failed.') from err

from setuptools import setup, Extension

# TODO legacy commment left by reference:
# Creates a relative path to this source file location on the filesystem,
# and then removes the last 64 characters of the str,
# that are the ones after the root of the project's path ( '/rumble_league_extension_plugin' )

# Get the absolute path of the current script
current_script_path = os.path.abspath(__file__)

# Get the directory containing the current script
script_directory = os.path.dirname(current_script_path)

# Navigate two directories above
rle_root = os.path.abspath(os.path.join(script_directory, '..', '..'))

print("RLE root directory: ", rle_root)


sfc_module = Extension(
    'rle', # Extension name
    language='c++',
    include_dirs = [
        pybind11.get_include(),
        "C:/opencv/build/include", # Adjust the path based on your installation
    ],
    libraries = ['opencv_world480'],  # Adjust the version number as needed
    library_dirs = ['C:/opencv/build/x64/vc16/lib'],  # Adjust the path based on your installation
    extra_compile_args = [
        # ... Your compiler options ...
    ],
    sources=[
        # Python bindings
        f'{rle_root}/python_mod/c++_bindings/python_linker.cpp',
        # Main library
        f'{rle_root}/core/RumbleLeague.cpp',
        # League Client screens and buttons
        f'{rle_root}/core/league_client/LeagueClientScreen.cpp',
        f'{rle_root}/core/league_client/LeagueClientButton.cpp',
        # Motion
        f'{rle_root}/motion/RumbleMotion.cpp',
        # Vision
        f'{rle_root}/vision/RumbleVision.cpp',
        # Window Capture
        f'{rle_root}/window_capture/WindowCapture.cpp',
        # Window Capture
        f'{rle_root}/helpers/StringHelper.cpp',
    ],
)

setup(
    name='Rumble LoL Extension',
    version='1.0.0',
    author='Alex Vergara',
    author_email='alex.vergara.dev@gmail.com',
    description='Python package that extends the Rumble-AI project with this module',
    ext_modules=[sfc_module],
)
