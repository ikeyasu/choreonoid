set(target PyCollisionSignalPlugin)
add_cnoid_python_module(${target} PyCollisionSignal.cpp)
target_link_libraries(${target} CnoidCollisionSignalPlugin CnoidPyBase)

