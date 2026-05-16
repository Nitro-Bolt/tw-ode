cmake_minimum_required(VERSION 3.11)
project(tw-ode)

add_subdirectory(ode)

add_executable(odejs odejs.c)
target_link_options(odejs PRIVATE
	"-sWASM=1"
	"-sSINGLE_FILE=1"
	"-sEXPORTED_FUNCTIONS=['_malloc', '_free', '_dInitODE2', '_dCloseODE', '_dDoCollision', '_dWorldStep', '_dWorldCreate', '_dHashSpaceCreate', '_dWorldDestroy', '_dSpaceDestroy', '_dWorldSetGravity', '_dJointGroupCreate', '_dJointGroupDestroy', '_dJointGroupEmpty', '_dBodyCreate', '_dBodySetMass', '_dCreateBox', '_dCreateCapsule', '_dCreateCylinder', '_dCreateSphere', '_dCreatePlane', '_dGeomSetBody', '_dGeomGetPosition', '_dGeomSetPosition', '_dGeomGetQuaternion', '_dGeomSetQuaternion', '_dMassSetBoxTotal', '_dMassSetCapsuleTotal', '_dMassSetCylinderTotal', '_dMassSetSphereTotal']"
	"-sEXPORTED_RUNTIME_METHODS=['cwrap', 'ccall', 'HEAPF64']"
	"-sMODULARIZE=1"
	"-sALLOW_TABLE_GROWTH=1"
	"-sALLOW_MEMORY_GROWTH=1"
	"-sSTACK_SIZE=1048576"
	"-sEXPORT_NAME=\"ODEWASM\""
)

target_link_libraries(odejs PRIVATE odewasm)

add_custom_command(TARGET odejs POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:odejs> ${CMAKE_SOURCE_DIR}/odejs.js
)
