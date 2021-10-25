from setuptools import setup, Extension
import pybind11

cpp_args = [
    "-IC:\\vcpkg\\installed\\x64-windows\\include",
    "-ID:\MSI 2020-2021\CODE\C++\RUMBLE LOL EXTENSION\X64\RELEASE",
    "/link",
    "/LIBPATH:C:\\vcpkg\\installed\\x64-windows\\lib",
    "/LIBPATH:C:\\vcpkg\\installed\\x64-windows\\bin",
    "/LIBPATH:D:\MSI 2020-2021\CODE\C++\RUMBLE LOL EXTENSION\X64\RELEASE",
    "/LIBPATH:C:\\vcpkg\\installed\\x64-windows\\lib\\*.lib",
    '/c "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\bin\HostX86\x64\link.exe"',
 ]

sfc_module = Extension(
    'rle',
    sources=[
        # Python bindings
        'D:\MSi 2020-2021\Code\C++\Rumble LoL Extension\python\c++_bindings\python_linker.cpp',
        # Main library
        'D:\MSi 2020-2021\Code\C++\Rumble LoL Extension\core\RumbleLeague.cpp',
        # League Client screens and buttons
        'D:\MSi 2020-2021\Code\C++\Rumble LoL Extension\core\league_client\LeagueClientScreen.cpp',
        'D:\MSi 2020-2021\Code\C++\Rumble LoL Extension\core\league_client\LeagueClientButton.cpp',
        # Motion
        'D:\MSi 2020-2021\Code\C++\Rumble LoL Extension\motion\RumbleMotion.cpp',
        # Vision
        'D:\MSi 2020-2021\Code\C++\Rumble LoL Extension\gision\RumbleVision.cpp',
        # Window Capture
        'D:\MSi 2020-2021\Code\C++\Rumble LoL Extension\window_capture\WindowCapture.cpp',
        # Window Capture
        'D:\MSi 2020-2021\Code\C++\Rumble LoL Extension\helpers\StringHelper.cpp',
    ],
    include_dirs=[pybind11.get_include()],
    language='c++',
    extra_compile_args=cpp_args,
    )

setup(
    name='Rumble LoL Extension',
    version='1.0',
    description='Python package that extends the Rumble-AI project with this module',
    ext_modules=[sfc_module],
)