#include <pybind11/pybind11.h>
#include <rumble_lol_plugin/RumbleLeague.hpp>

namespace py = pybind11;

PYBIND11_MODULE(rlp, m) {
    py::class_<RumbleLeague>(m, "RumbleLeague")
        .def(py::init<>())
        .def(py::init<const int &, const bool&, const bool &>())
        .def("play", &RumbleLeague::play);
}


// cmake -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:/msys64/mingw64/bin/clang++.exe -DCMAKE_CXX_FLAGS="-target x86_64-pc-windows-gnu"