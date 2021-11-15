#include <pybind11/pybind11.h>
#include "../../core/RumbleLeague.hpp"

namespace py = pybind11;

PYBIND11_MODULE(rle, m) {
    py::class_<RumbleLeague>(m, "RumbleLeague")
        .def(py::init<>())
        .def(py::init<const int &, const bool&, const bool &>())
        .def("play", &RumbleLeague::play);
}