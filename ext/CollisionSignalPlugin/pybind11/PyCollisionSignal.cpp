/*!
 * @author Yasui Ikeuchi
 */

#include "../CollisionSignalPlugin.h"
#include <cnoid/PyBase>

using namespace cnoid;
namespace py = pybind11;

namespace cnoid {

void exportClasses(py::module m){
    py::class_<CollisionSignalItem, CollisionSignalItemPtr, SubSimulatorItem> itemClass(m, "CollisionSignalItem");
    itemClass
        .def(py::init<>())
        .def("sigCollisioned", &CollisionSignalItem::sigCollisioned);
}
}

PYBIND11_MODULE(CollisionSignalPlugin, m)
{
    m.doc() = "Choreonoid CollisionSignal module";
    py::module::import("cnoid.BodyPlugin");
    exportClasses(m);
}

