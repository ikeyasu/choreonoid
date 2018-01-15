/*!
  @file
  @author Yasuki Ikeuchi
*/

#include "CollisionSignalPlugin.h"
#include <cnoid/LazyCaller>



namespace {

class CollisionSignalPlugin : public Plugin
{
public:
    CollisionSignalPlugin() : Plugin("CollisionSignal") {
        require("Body");
    }

    virtual bool initialize() {
        itemManager()
            .registerClass<CollisionSignalItem>("CollisionSignalItem")
            .addCreationPanel<CollisionSignalItem>();
        return true;
    }
};

}

CollisionSignalItem::CollisionSignalItem()
{

}


CollisionSignalItem::CollisionSignalItem(const CollisionSignalItem& org)
    : SubSimulatorItem(org)
{

}


Item* CollisionSignalItem::doDuplicate() const
{
    return new CollisionSignalItem(*this);
}

void CollisionSignalItem::onPositionChanged()
{
    AISTSimulatorItem* simulator = findOwnerItem<AISTSimulatorItem>();
    AISTSimulatorItem* currentSimulator = weakCurrentSimulator.lock();
    if(simulator != currentSimulator){
        if(currentSimulator){
            currentSimulator->unregisterCollisionHandler("CollisionSignal");
            weakCurrentSimulator.reset();
        }
        if(simulator){
            simulator->registerCollisionHandler(
                "CollisionSignal",
                [&](Link* link1, Link* link2, const CollisionArray& collisions, ContactMaterial* cm){
                    return calcContactForce(link1, link2, collisions, cm); });
            
            weakCurrentSimulator = simulator;
        }
    }
}


bool CollisionSignalItem::initializeSimulation(SimulatorItem* simulatorItem)
{
    return true;
}


bool CollisionSignalItem::calcContactForce
(Link* link1, Link* link2, const CollisionArray& collisions, ContactMaterial* cm)
{
    callLater([&](){
    	sigCollisioned_();
    });
    return true;
}

CNOID_IMPLEMENT_PLUGIN_ENTRY(CollisionSignalPlugin);

