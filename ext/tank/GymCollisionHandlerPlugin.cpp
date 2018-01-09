/*!
  @file
  @author Yasuki Ikeuchi
*/

#include "GymCollisionHandlerPlugin.h"
#include <cnoid/LazyCaller>



namespace {

class GymCollisionHandlerPlugin : public Plugin
{
public:
    GymCollisionHandlerPlugin() : Plugin("GymCollisionHandler") {
        require("Body");
    }

    virtual bool initialize() {
        itemManager()
            .registerClass<GymCollisionHandlerItem>("GymCollisionHandlerItem")
            .addCreationPanel<GymCollisionHandlerItem>();
        return true;
    }
};

}

GymCollisionHandlerItem::GymCollisionHandlerItem()
{

}


GymCollisionHandlerItem::GymCollisionHandlerItem(const GymCollisionHandlerItem& org)
    : SubSimulatorItem(org)
{

}


Item* GymCollisionHandlerItem::doDuplicate() const
{
    return new GymCollisionHandlerItem(*this);
}


void GymCollisionHandlerItem::setCollisionHandler(pybind11::function callback)
{
	//collisionPythonCallback = std::make_shared<pybind11::object>(callback);
	collisionPythonCallback = callback;
//	collisionPythonCallback.inc_ref();
//	callFromMainThread([&](){
//    	 collisionPythonCallback();
//    });
//	collisionPythonCallback();
}

pybind11::function GymCollisionHandlerItem::getCollisionHandler()
{
	return collisionPythonCallback;
}

void GymCollisionHandlerItem::onPositionChanged()
{
    mvout() << "======> GYM: onPositionChanged" << std::endl;
    AISTSimulatorItem* simulator = findOwnerItem<AISTSimulatorItem>();
    AISTSimulatorItem* currentSimulator = weakCurrentSimulator.lock();
    if(simulator != currentSimulator){
        if(currentSimulator){
            mvout() << "unregisterCollisionHandler" << std::endl;
            currentSimulator->unregisterCollisionHandler("GymCollisionHandler");
            weakCurrentSimulator.reset();
        }
        if(simulator){
            mvout() << "======> GYM: registerCollisionHandler" << std::endl;
            simulator->registerCollisionHandler(
                "GymCollisionHandler",
                [&](Link* link1, Link* link2, const CollisionArray& collisions, ContactMaterial* cm){
                    return calcContactForce(link1, link2, collisions, cm); });
            
            weakCurrentSimulator = simulator;
        }
    }
}


bool GymCollisionHandlerItem::initializeSimulation(SimulatorItem* simulatorItem)
{
    mvout() << "======> GYM: initializeSimulation" << std::endl;
    return true;
}


bool GymCollisionHandlerItem::calcContactForce
(Link* link1, Link* link2, const CollisionArray& collisions, ContactMaterial* cm)
{
//    mvout() << "=====> GYM:" << collisions.size() << std::endl;
//  	pybind11::object *func = collisionPythonCallback.get();
//  	if (func) {
//  		(*func)();
//  	}
//    callLater([&](){
//    	 collisionPythonCallback();
//    });
    collisionPythonCallback();
    return true;
}

CNOID_IMPLEMENT_PLUGIN_ENTRY(GymCollisionHandlerPlugin);

