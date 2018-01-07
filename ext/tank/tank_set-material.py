from cnoid.Base import *
from cnoid.BodyPlugin import *

tank = Item.find("Tank").body()
#tank.link("CHASSIS").setMaterial("Tank")
#CHASSIS
#TURRET_Y
#TURRET_P
#TRACK_L
#TRACK_R
tank.link("CHASSIS").setMaterial("Tank")
tank.link("TURRET_Y").setMaterial("Tank")
tank.link("TURRET_P").setMaterial("Tank")
#tank.link("TRACK_L").setMaterial("Tank")
#tank.link("TRACK_R").setMaterial("Tank")

floor = Item.find("box2").body()
floor.rootLink().setMaterial("Box")

print("=====>tank_set-material.py")
