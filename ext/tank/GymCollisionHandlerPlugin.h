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
#include <cnoid/PyBase>
#include <memory>
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
    void setCollisionHandler(pybind11::function callback);
    pybind11::function getCollisionHandler();

protected:
    virtual Item* doDuplicate() const;

private:
    bool calcContactForce(Link* link1, Link* link2, const CollisionArray& collisions, ContactMaterial* cm);

    weak_ref_ptr<AISTSimulatorItem> weakCurrentSimulator;
    //shared_ptr<pybind11::object> collisionPythonCallback;
    pybind11::function collisionPythonCallback;
};

typedef ref_ptr<GymCollisionHandlerItem> GymCollisionHandlerItemPtr;
}

#endif
