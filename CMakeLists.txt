cmake_minimum_required(VERSION 3.11)
project(tw-ode)

set(ODE_TARGET odewasm)

add_subdirectory(ode)
add_executable(odejs odejs.c)
target_link_options(odejs PRIVATE
	"-sWASM=1"
	"-sSINGLE_FILE=1"
	"-sEXPORTED_FUNCTIONS=['_malloc', '_free', '_dInitODE2', '_dCloseODE', '_dDoCollision', '_dWorldStep', '_dWorldCreate', '_dHashSpaceCreate', '_dWorldDestroy', '_dSpaceDestroy', '_dWorldSetGravity', '_dJointGroupCreate', '_dJointGroupDestroy', '_dJointGroupEmpty', '_dBodyCreate', '_dBodyDestroy', '_dBodyInitMass', '_dBodyGetPosition', '_dBodySetPosition', '_dBodyGetQuaternion', '_dBodySetQuaternion', '_dBodyAddForce', '_dBodyGetForce', '_dBodySetForce', '_dBodyGetLinearDamping', '_dBodyGetAngularDamping', '_dBodySetLinearDamping', '_dBodySetAngularDamping', '_dBodyIsKinematic', '_dBodySetKinematic', '_dBodySetDynamic', '_dCreateBox', '_dCreateCapsule', '_dCreateCylinder', '_dCreateSphere', '_dCreatePlane', '_dCustomCreateTriMesh', '_dCustomCreateHeightfield', '_dGeomCustomDestroy', '_dGeomSetBody', '_dGeomGetPosition', '_dGeomSetPosition', '_dGeomGetQuaternion', '_dGeomSetQuaternion', '_dJointCreateBall', '_dJointCreateDBall', '_dJointCreateDHinge', '_dJointCreateFixed', '_dJointCreateHinge', '_dJointCreateHinge2', '_dJointCreateLMotor', '_dJointCreatePiston', '_dJointCreatePlane2D', '_dJointCreatePR', '_dJointCreatePU', '_dJointCreateSlider', '_dJointCreateTransmission', '_dJointCreateUniversal', '_dJointDestroy', '_dJointGroupDestroy', '_dJointGroupEmpty', '_dJointAttach', '_dJointSetBallAnchor', '_dJointGetBallAnchor', '_dJointGetBallAnchor2', '_dJointSetHingeAnchor', '_dJointSetHingeAxis', '_dJointGetHingeAnchor', '_dJointGetHingeAnchor2', '_dJointGetHingeAxis', '_dJointGetHingeAngle', '_dJointSetSliderAxis', '_dJointGetSliderAxis', '_dJointGetSliderPosition', '_dJointSetUniversalAnchor', '_dJointSetUniversalAxis1', '_dJointSetUniversalAxis2', '_dJointGetUniversalAnchor', '_dJointGetUniversalAnchor2', '_dJointGetUniversalAxis1', '_dJointGetUniversalAxis2', '_dJointGetUniversalAngle1', '_dJointGetUniversalAngle2', '_dJointSetHinge2Anchor', '_dJointSetHinge2Axis1', '_dJointSetHinge2Axis2', '_dJointGetHinge2Anchor', '_dJointGetHinge2Anchor2', '_dJointGetHinge2Axis1', '_dJointGetHinge2Axis2', '_dJointGetHinge2Angle1', '_dJointSetPRAxis1', '_dJointGetPRAxis1', '_dJointSetPRAxis2', '_dJointGetPRAxis2', '_dJointSetPRAnchor', '_dJointGetPRAnchor', '_dJointSetPUAnchor', '_dJointGetPUAnchor', '_dJointSetPUAxis1', '_dJointGetPUAxis1', '_dJointSetPUAxis2', '_dJointGetPUAxis2', '_dJointSetPUAxis3', '_dJointGetPUAxis3', '_dJointGetPUAngle1', '_dJointGetPUAngle2', '_dJointSetPistonAnchor', '_dJointGetPistonAnchor', '_dJointGetPistonAnchor2', '_dJointSetPistonAxis', '_dJointGetPistonAxis', '_dJointGetPistonPosition', '_dJointGetPistonAngle', '_dJointAddPistonForce', '_dJointSetLMotorAxis', '_dJointGetLMotorAxis', '_dJointAddHingeTorque', '_dJointAddUniversalTorques', '_dJointAddSliderForce', '_dJointAddHinge2Torques', '_dJointGetTransmissionAnchor1', '_dJointGetDBallAnchor1', '_dJointGetDHingeAnchor1', '_dJointSetTransmissionAnchor1', '_dJointSetDBallAnchor1', '_dJointSetDHingeAnchor1', '_dJointGetTransmissionAnchor2', '_dJointGetDBallAnchor2', '_dJointGetDHingeAnchor2', '_dJointSetBallAnchor2', '_dJointSetTransmissionAnchor2', '_dJointSetDBallAnchor2', '_dJointSetDHingeAnchor2', '_dJointGetTransmissionAxis1', '_dJointGetDHingeAxis', '_dJointSetTransmissionAxis1', '_dJointSetDHingeAxis', '_dJointGetTransmissionAxis2', '_dJointSetTransmissionAxis2', '_dJointGetPRAngle', '_dJointGetTransmissionAngle1', '_dJointGetTransmissionAngle2', '_dJointAddPRTorque', '_dJointAddPUTorques', '_dRaycast', '_dRaycastGeom']"
	"-sEXPORTED_RUNTIME_METHODS=['cwrap', 'ccall', 'HEAPU32', 'HEAPF64']"
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
