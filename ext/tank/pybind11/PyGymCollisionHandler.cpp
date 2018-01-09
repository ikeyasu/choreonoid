/*!
 * @author Yasui Ikeuchi
 */

#include "../GymCollisionHandlerPlugin.h"
#include <cnoid/PyBase>

using namespace cnoid;
namespace py = pybind11;

namespace cnoid {

void exportClasses(py::module m){
    py::class_<GymCollisionHandlerItem, GymCollisionHandlerItemPtr, SubSimulatorItem> itemClass(m, "GymCollisionHandlerItem");
    itemClass
        .def(py::init<>())
        .def("sigCollisioned", &GymCollisionHandlerItem::sigCollisioned);
}
}

PYBIND11_MODULE(GymCollisionHandlerPlugin, m)
{
    m.doc() = "Choreonoid GymCollisionHandler module";
    py::module::import("cnoid.BodyPlugin");
    exportClasses(m);
}

