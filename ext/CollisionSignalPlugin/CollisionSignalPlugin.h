/*!
  @file
  @author Yasuki Ikeuchi
*/

#ifndef CNOID_COLLISION_SIGNAL_PLUGIN_H_INCLUDED
#define CNOID_COLLISION_SIGNAL_PLUGIN_H_INCLUDED

#include <cnoid/Plugin>
#include <cnoid/ItemManager>
#include <cnoid/SubSimulatorItem>
#include <cnoid/AISTSimulatorItem>
#include <cnoid/ContactMaterial>
#include <cnoid/PyBase>
#include <memory>

using namespace std;
using namespace cnoid;

namespace cnoid {

class CNOID_EXPORT CollisionSignalItem : public SubSimulatorItem
{
public:
    static void initializeClass(ExtensionManager* ext);
        
    CollisionSignalItem();
    CollisionSignalItem(const CollisionSignalItem& org);
    virtual void onPositionChanged();
    virtual bool initializeSimulation(SimulatorItem* simulatorItem);
    SignalProxy<void()> sigCollisioned() {
        return sigCollisioned_;
    }

protected:
    virtual Item* doDuplicate() const;

private:
    bool calcContactForce(Link* link1, Link* link2, const CollisionArray& collisions, ContactMaterial* cm);

    weak_ref_ptr<AISTSimulatorItem> weakCurrentSimulator;
    Signal<void()> sigCollisioned_;
};

typedef ref_ptr<CollisionSignalItem> CollisionSignalItemPtr;
}

#endif
