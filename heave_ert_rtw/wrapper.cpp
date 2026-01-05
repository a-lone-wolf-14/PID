#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "heave.h"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(heave_rt, m)
{
    // =================== Heave Model Class ===================
    py::class_<heave>(m, "Heave")
        .def(py::init<>())

        // ======= step functions (INSTANCE) =======
        .def("step", &heave::step)     // base rate
        .def("step1", &heave::step1)   // subrate

        // ======= inputs =======
        .def(
            "set_inputs",
            [](heave &self, double depth_goal, double depth)
            {
                self.rtU.depth_goal = depth_goal;
                self.rtU.depth = depth;
            },
            py::arg("depth_goal"),
            py::arg("depth")
        )

        // ======= outputs =======
        .def(
            "outputs",
            [](heave &self)
            {
                return py::dict(
                    "FL"_a = self.rtY.FL,
                    "FR"_a = self.rtY.FR,
                    "BL"_a = self.rtY.BL,
                    "BR"_a = self.rtY.BR
                );
            }
        );

    // =================== STATIC lifecycle ===================
    // Simulink ERT: initialize() is STATIC → module-level
    m.def("initialize", &heave::initialize, "Initialize the heave model");
}

