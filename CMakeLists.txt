cmake_minimum_required(VERSION 3.11)
project(tw-ode)

set(ODE_TARGET odewasm)

add_subdirectory(ode)
add_executable(odejs odejs.c)
target_link_options(odejs PRIVATE
	"-sWASM=1"
	"-sSINGLE_FILE=1"
	"-sEXPORTED_FUNCTIONS=['_malloc', '_free', '_dInitODE2', '_dCloseODE', '_dDoCollision', '_dWorldStep', '_dWorldCreate', '_dHashSpaceCreate', '_dWorldDestroy', '_dSpaceDestroy', '_dWorldSetGravity', '_dJointGroupCreate', '_dJointGroupDestroy', '_dJointGroupEmpty', '_dBodyCreate', '_dBodyDestroy', '_dBodyInitMass', '_dBodyGetPosition', '_dBodySetPosition', '_dBodyGetQuaternion', '_dBodySetQuaternion', '_dBodyAddForce', '_dBodyGetForce', '_dBodySetForce', '_dBodyGetLinearDamping', '_dBodyGetAngularDamping', '_dBodySetLinearDamping', '_dBodySetAngularDamping', '_dBodyIsKinematic', '_dBodySetKinematic', '_dBodySetDynamic', '_dCreateBox', '_dCreateCapsule', '_dCreateCylinder', '_dCreateSphere', '_dCreatePlane', '_dGeomDestroy', '_dGeomSetBody', '_dGeomGetPosition', '_dGeomSetPosition', '_dGeomGetQuaternion', '_dGeomSetQuaternion', '_dJointCreateAMotor', '_dJointCreateBall', '_dJointCreateDBall', '_dJointCreateDHinge', '_dJointCreateFixed', '_dJointCreateHinge', '_dJointCreateHinge2', '_dJointCreateLMotor', '_dJointCreatePiston', '_dJointCreatePlane2D', '_dJointCreatePR', '_dJointCreatePU', '_dJointCreateSlider', '_dJointCreateTransmission', '_dJointDestroy', '_dRaycast', '_dRaycastGeom']"
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
