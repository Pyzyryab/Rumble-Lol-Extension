#include <pybind11/pybind11.h>
#include <rumble_lol_plugin/RumbleLeague.hpp>

namespace py = pybind11;

PYBIND11_MODULE(rlp, m) {
    py::class_<RumbleLeague>(m, "RumbleLeague")
        .def(py::init<>())
        .def(py::init<const int &, const bool&, const bool &>())
        .def("play", &RumbleLeague::play);

    m.doc() = "Rumble-AI Plugin with the functionality to control the League of Legends client";
}
