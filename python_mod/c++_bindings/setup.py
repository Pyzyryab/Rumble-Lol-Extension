# Creates a relative path to this source file location on the filesystem
import subprocess
import sys
from pathlib import Path
from setuptools import setup, Extension

BASE_PATH = str(Path(__file__).absolute())[ : - 33 ]

try:
    import pybind11
except ImportError:
    if subprocess.call([sys.executable, '-m', 'pip', 'install', 'pybind11']):
        raise RuntimeError('pybind11 install failed.')

import pybind11

# Set path separator slashes according to the current OS
SEP = '\\' if sys.platform.startswith("win32") else '/'


builder_cfg = Extension(
    'rle',
    sources = [
        # Python bindings
        f'{BASE_PATH}{SEP}python_mod{SEP}c++_bindings{SEP}python_linker.cpp',
        # Main library
        f'{BASE_PATH}{SEP}core{SEP}RumbleLeague.cpp',
        # League Client screens and buttons
        f'{BASE_PATH}{SEP}core{SEP}league_client{SEP}LeagueClientScreen.cpp',
        f'{BASE_PATH}{SEP}core{SEP}league_client{SEP}LeagueClientButton.cpp',
        # Motion
        f'{BASE_PATH}{SEP}motion{SEP}RumbleMotion.cpp',
        # Vision
        f'{BASE_PATH}{SEP}vision{SEP}RumbleVision.cpp',
        # Window Capture
        f'{BASE_PATH}{SEP}window_capture{SEP}WindowCapture.cpp',
        # Window Capture
        f'{BASE_PATH}{SEP}helpers{SEP}StringHelper.cpp',
        # Actions
        f'{BASE_PATH}{SEP}core{SEP}actions{SEP}ClickScreenButton.cpp',
    ],
    include_dirs = [
        pybind11.get_include(),
        f"{BASE_PATH}{SEP}include"
    ],
    library_dirs = [
        f"{BASE_PATH}{SEP}include{SEP}opencv2_libs",
        f"{BASE_PATH}{SEP}include{SEP}windows"
    ],
    libraries = [
        'opencv_core', 'opencv_highgui', 'opencv_imgcodecs', 'opencv_imgproc',
        'kernel32', 'user32', 'gdi32', 'comdlg32'
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