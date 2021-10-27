# Gets an absolute path to this file, and delete the characters on the str that represents the 
# inner paths of the root path ( 'rumble_league_extension_plugin' )
from pathlib import Path
rel_path = str(Path(__file__).absolute())[ : -64 ]

from setuptools import setup, Extension
import pybind11

cpp_args = [
    "-IC:\\vcpkg\\installed\\x64-windows\\include",
    f"-I{rel_path}\\rumble_league_extension_plugin\RUMBLE LOL EXTENSION\X64\RELEASE",
    "/link",
    "/LIBPATH:C:\\vcpkg\\installed\\x64-windows\\lib",
    "/LIBPATH:C:\\vcpkg\\installed\\x64-windows\\bin",
    f"/LIBPATH:{rel_path}\\rumble_league_extension_plugin\X64\RELEASE",
    "/LIBPATH:C:\\vcpkg\\installed\\x64-windows\\lib\\*.lib",
    '/c "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\bin\HostX86\x64\link.exe"',
 ]

sfc_module = Extension(
    'rle',
    sources=[
        # Python bindings
        f'{rel_path}\\rumble_league_extension_plugin\python_mod\c++_bindings\python_linker.cpp',
        # Main library
        f'{rel_path}\\rumble_league_extension_plugin\core\RumbleLeague.cpp',
        # League Client screens and buttons
        f'{rel_path}\\rumble_league_extension_plugin\core\league_client\LeagueClientScreen.cpp',
        f'{rel_path}\\rumble_league_extension_plugin\core\league_client\LeagueClientButton.cpp',
        # Motion
        f'{rel_path}\\rumble_league_extension_plugin\motion\RumbleMotion.cpp',
        # Vision
        f'{rel_path}\\rumble_league_extension_plugin\gision\RumbleVision.cpp',
        # Window Capture
        f'{rel_path}\\rumble_league_extension_plugin\window_capture\WindowCapture.cpp',
        # Helpers
        f'{rel_path}\\rumble_league_extension_plugin\helpers\StringHelper.cpp',
    ],
    include_dirs=[pybind11.get_include()],
    language='c++',
    extra_compile_args=cpp_args,
    )

setup(
    name='Rumble LoL Extension',
    version='1.0.0',
    description='''Extension to Rumble-AI that manages to control the League of Legends client by voice. 
    Also performs several other tasks, included in-game ones''',
    ext_modules=[sfc_module],
)