"""
Rumble LoL Extension

This is a Python package that extends the Rumble-AI project with a C++ module.

Usage (from the root directory):
    $ pip install ./python/c++_bindings
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

# TODO legacy comment left by reference:
# Creates a relative path to this source file location on the filesystem,
# and then removes the last 64 characters of the str,
# that are the ones after the root of the project's path ( '/rumble_league_extension_plugin' )

# Get the absolute path of the current script
current_script_path = os.path.abspath(__file__)

# Get the directory containing the current script
script_directory = os.path.dirname(current_script_path)

# Navigate two directories above
rle_root = os.path.abspath(os.path.join(script_directory, '..', '..'))

# The code root directory
rle_code_dir = os.path.join(rle_root, 'code')

# The source code directory, following the guidelines of
# https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1204r0.html
rle_code_root = os.path.join(rle_code_dir, 'code', 'rumble_lol_plugin')

print(f'RLE root directory: {rle_root}\n RLE SRC root dir: {rle_code_root}')

# Keep in mind that this method of building the project relies on you having a valid installation
# of OpenCV and pybind11, with your installations set up according to the paths described below,
# or that you'll adjust them to better suit your local setup.

sfc_module = Extension(
    name='rlp',  # The name of the generated Python module
    language='c++',
    include_dirs=[
        pybind11.get_include(),
        "C:/opencv/build/include",  # Adjust the path based on your installation
        # Our code include path
        rle_code_dir,
        rle_code_root
    ],
    libraries=['opencv_world480'],  # Adjust the version number as needed
    library_dirs=['C:/opencv/build/x64/vc16/lib'],  # Adjust the path based on your installation
    extra_compile_args=[
        # ... Your compiler options ...
    ],
    sources=[
        # C++ -> Python FFI
        f'{rle_code_root}/ffi/rlp.cpp',
        # Core
        f'{rle_code_root}/RumbleLeague.cpp',
        # League Client screens and buttons
        f'{rle_code_root}/league_client/screen.cpp',
        f'{rle_code_root}/league_client/button.cpp',
        # Motion
        f'{rle_code_root}/motion/motion.cpp',
        # Vision
        f'{rle_code_root}/vision/vision.cpp',
        # Writer (non ready yeat)
        # f'{rle_code_root}/writer/writer.cpp',
        # Window Capture
        f'{rle_code_root}/capture/window_capture.cpp',
        # Helpers
        f'{rle_code_root}/helpers/string.cpp',
    ],
)

setup(
    name='Rumble LoL Plugin',
    version='0.1.0',
    author='Alex Vergara',
    author_email='alex.vergara.dev@gmail.com',
    description='Python package that extends the Rumble-AI project with this module',
    ext_modules=[sfc_module],
)
