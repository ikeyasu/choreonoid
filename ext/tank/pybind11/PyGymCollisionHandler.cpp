/*!
 * @author Yasui Ikeuchi
 */

#include "../GymCollisionHandlerPlugin.h"
#include <cnoid/PyBase>

using namespace cnoid;
namespace py = pybind11;

namespace cnoid {

void exportClasses(py::module m){
    mvout() << "======> GYM: exportClasses" << std::endl;
    py::class_<GymCollisionHandlerItem, GymCollisionHandlerItemPtr, SubSimulatorItem> itemClass(m, "GymCollisionHandlerItem");
    itemClass
        .def(py::init<>())
        .def("test_callback1", [](py::object self, py::object func) { return func(); })
        .def("test1", &GymCollisionHandlerItem::test1);
}
}

PYBIND11_MODULE(GymCollisionHandlerPlugin, m)
{
    m.doc() = "Choreonoid GymCollisionHandler module";
    py::module::import("cnoid.BodyPlugin");
    exportClasses(m);
}

