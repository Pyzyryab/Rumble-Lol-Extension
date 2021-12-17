# Creates a relative path to this source file location on the filesystem, and then removes the last 33 characters of the str
# that are the ones after the root of the project's path ( '\\rumble_league_extension_plugin' )
from pathlib import Path
rel_path = str(Path(__file__).absolute())[ : - 33 ]

import subprocess
import sys

from setuptools import setup, Extension

try:
    import pybind11
except ImportError:
    if subprocess.call([sys.executable, '-m', 'pip', 'install', 'pybind11']):
        raise RuntimeError('pybind11 install failed.')


import pybind11

# cpp_args = [
#     f"D:\\MSi 2020-2021\\Code\\Python\\Rumble-AI\\src\\plugins\\rumble_league_extension_plugin\\include\\opencv2_libs\\opencv_core.lib"
#     f"D:\\MSi 2020-2021\\Code\\Python\\Rumble-AI\\src\\plugins\\rumble_league_extension_plugin\\include\\opencv2_libs\\opencv_highgui.lib"
#     f"D:\\MSi 2020-2021\\Code\\Python\\Rumble-AI\\src\\plugins\\rumble_league_extension_plugin\\include\\opencv2_libs\\opencv_imgproc.lib"
#     f"D:\\MSi 2020-2021\\Code\\Python\\Rumble-AI\\src\\plugins\\rumble_league_extension_plugin\\include\\opencv2_libs\\opencv_imgcodecs.lib",
#     f"-I{rel_path}\\include"
# ]

builder_cfg = Extension(
    'rle',
    sources = [
        # Python bindings
        f'{rel_path}\\python_mod\c++_bindings\python_linker.cpp',
        # Main library
        f'{rel_path}\\core\RumbleLeague.cpp',
        # League Client screens and buttons
        f'{rel_path}\\core\league_client\LeagueClientScreen.cpp',
        f'{rel_path}\\core\league_client\LeagueClientButton.cpp',
        # Motion
        f'{rel_path}\\motion\RumbleMotion.cpp',
        # Vision
        f'{rel_path}\\vision\RumbleVision.cpp',
        # Window Capture
        f'{rel_path}\\window_capture\WindowCapture.cpp',
        # Window Capture
        f'{rel_path}\\helpers\StringHelper.cpp',
        # Actions
        f'{rel_path}\\core\\actions\\Actions.cpp',
    ],
    include_dirs = [
        pybind11.get_include(),
        f"{rel_path}\\include"
    ],
    library_dirs = [
        f"{rel_path}\\include\\opencv2_libs"
    ],
    libraries = [
        'opencv_core', 'opencv_highgui', 'opencv_imgcodecs', 'opencv_imgproc'
    ],
    language='c++'
)

setup(
    name='Rumble LoL Extension',
    version='1.0.0',
    author='Alex Vergara',
    author_email='alex10.vergara@gmail.com',
    description='Python package that extends the Rumble-AI project with this module',
    ext_modules=[builder_cfg],
)