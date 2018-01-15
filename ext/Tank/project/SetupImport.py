from cnoid.GymCollisionHandlerPlugin import *
GymCollisionHandlerItem.find("GymCollisionHandler").sigCollisioned().connect(lambda: print("=====> Collisioned"))
