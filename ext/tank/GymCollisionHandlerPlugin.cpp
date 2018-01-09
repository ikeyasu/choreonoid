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

void GymCollisionHandlerItem::onPositionChanged()
{
    AISTSimulatorItem* simulator = findOwnerItem<AISTSimulatorItem>();
    AISTSimulatorItem* currentSimulator = weakCurrentSimulator.lock();
    if(simulator != currentSimulator){
        if(currentSimulator){
            currentSimulator->unregisterCollisionHandler("GymCollisionHandler");
            weakCurrentSimulator.reset();
        }
        if(simulator){
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
    return true;
}


bool GymCollisionHandlerItem::calcContactForce
(Link* link1, Link* link2, const CollisionArray& collisions, ContactMaterial* cm)
{
    callLater([&](){
    	sigCollisioned_();
    });
    return true;
}

CNOID_IMPLEMENT_PLUGIN_ENTRY(GymCollisionHandlerPlugin);

