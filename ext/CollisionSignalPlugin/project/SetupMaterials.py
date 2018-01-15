from cnoid.Base import *
from cnoid.BodyPlugin import *
from cnoid.CollisionSignalPlugin import *

tank = Item.find("Tank").body()
tank.link("CHASSIS").setMaterial("Tank")
tank.link("TURRET_Y").setMaterial("Tank")
tank.link("TURRET_P").setMaterial("Tank")
#tank.link("TRACK_L").setMaterial("Tank")
#tank.link("TRACK_R").setMaterial("Tank")

floor = Item.find("box2").body()
floor.rootLink().setMaterial("Box")

CollisionSignalItem.find("CollisionSignal").sigCollisioned().connect(lambda: print("=====> Collisioned"))
