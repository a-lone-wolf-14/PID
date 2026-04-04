#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "roll.h"

namespace py = pybind11;

class RollWrapper {
public:
    RollWrapper() {
        model.initialize();
        subrate_counter = 0;
    }

    void set_inputs(double roll_goal,
                    double roll_h,
                    double roll_rate,
                    double heave)
    {
        model.rtU.roll_goal = roll_goal;
        model.rtU.roll_h    = roll_h;
        model.rtU.roll_rate = roll_rate;
        model.rtU.heave     = heave;
    }

    // Call this at 1 kHz
    void step()
    {
        model.step0();              // base rate: 1 kHz

        subrate_counter++;
        if (subrate_counter >= 10)  // 100 Hz subrate
        {
            model.step1();
            subrate_counter = 0;
        }
    }

    py::dict outputs() const
    {
        py::dict d;
        d["FL"] = model.rtY.FL;
        d["FR"] = model.rtY.FR;
        d["BL"] = model.rtY.BL;
        d["BR"] = model.rtY.BR;
        return d;
    }

private:
    roll model;
    int subrate_counter;
};

PYBIND11_MODULE(roll_ctrl, m)
{
    m.doc() = "Roll DOF controller (Simulink ERT generated)";

    py::class_<RollWrapper>(m, "RollController")
        .def(py::init<>())
        .def("set_inputs", &RollWrapper::set_inputs,
             py::arg("roll_goal"),
             py::arg("roll"),
             py::arg("roll_rate"),
             py::arg("heave"))
        .def("step", &RollWrapper::step)
        .def("outputs", &RollWrapper::outputs);
}
