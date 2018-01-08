/*!
  @file
  @author Yasuki Ikeuchi
*/

#ifndef CNOID_GYM_COLLISION_HANDLER_PLUGIN_H_INCLUDED
#define CNOID_GYM_COLLISION_HANDLER_PLUGIN_H_INCLUDED

#include <cnoid/Plugin>
#include <cnoid/ItemManager>
#include <cnoid/SubSimulatorItem>
#include <cnoid/AISTSimulatorItem>
#include <cnoid/ContactMaterial>
#include "exportdecl.h"

using namespace std;
using namespace cnoid;

namespace cnoid {

class CNOID_EXPORT GymCollisionHandlerItem : public SubSimulatorItem
{
public:
    static void initializeClass(ExtensionManager* ext);
        
    GymCollisionHandlerItem();
    GymCollisionHandlerItem(const GymCollisionHandlerItem& org);
    virtual void onPositionChanged();
    virtual bool initializeSimulation(SimulatorItem* simulatorItem);
    void test1();

protected:
    virtual Item* doDuplicate() const;

private:
    bool calcContactForce(Link* link1, Link* link2, const CollisionArray& collisions, ContactMaterial* cm);

    weak_ref_ptr<AISTSimulatorItem> weakCurrentSimulator;
};

typedef ref_ptr<GymCollisionHandlerItem> GymCollisionHandlerItemPtr;
}

#endif
