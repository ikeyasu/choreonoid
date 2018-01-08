set(target PyGymCollisionHandlerPlugin)
add_cnoid_python_module(${target} PyGymCollisionHandler.cpp)
target_link_libraries(${target} CnoidGymCollisionHandlerPlugin CnoidPyBase)

