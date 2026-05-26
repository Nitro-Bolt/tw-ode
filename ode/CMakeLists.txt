cmake_minimum_required(VERSION 3.11)

if(NOT DEFINED ODE_TARGET)
	set(ODE_TARGET ode)
endif()

project(${ODE_TARGET})

set(BASE ../../ode)
set(TRIMESH OPCODE)

if(TRIMESH STREQUAL "OPCODE")
	set(TRIMESH_SRC ${BASE}/OPCODE/*.cpp ${BASE}/OPCODE/Ice/*.cpp)
else()
	set(TRIMESH_SRC ${BASE}/GIMPACT/src/*.cpp)
endif()

file(GLOB ODE_SRC
	${BASE}/ode/src/*.c
	${BASE}/ode/src/*.cpp
	${BASE}/ode/src/joints/*.cpp
	${BASE}/ou/src/ou/*.cpp
	${TRIMESH_SRC}
	${BASE}/libccd/src/*.c
)

add_library(${ODE_TARGET} STATIC ${ODE_SRC})
target_include_directories(${ODE_TARGET} PUBLIC
	${BASE}/include
	${CMAKE_CURRENT_BINARY_DIR}
)
target_include_directories(${ODE_TARGET} PRIVATE
	${BASE}/ode/src
	${BASE}/ode/src/joints
	${BASE}/OPCODE
	${BASE}/ou/include
	${BASE}/GIMPACT/include
	${BASE}/libccd/src/custom
	${BASE}/libccd/src
)

list(REMOVE_ITEM ODE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/${BASE}/ode/src/collision_trimesh_trimesh_old.cpp)
list(REMOVE_ITEM ODE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/${BASE}/ode/src/collision_trimesh_opcode.cpp)
list(REMOVE_ITEM ODE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/${BASE}/ode/src/collision_trimesh_disabled.cpp)

target_compile_definitions(${ODE_TARGET} PRIVATE
	_OU_NAMESPACE=odeou
	_OU_FEATURE_SET=_OU_FEATURE_SET_TLS
	dLIBCCD_ENABLED
	dLIBCCD_INTERNAL
	dLIBCCD_BOX_CYL
	dLIBCCD_CYL_CYL
	dLIBCCD_CAP_CYL
	dLIBCCD_CONVEX_BOX
	dLIBCCD_CONVEX_CAP
	dLIBCCD_CONVEX_CYL
	dLIBCCD_CONVEX_SPHERE
	dLIBCCD_CONVEX_CONVEX
)

target_link_libraries(${ODE_TARGET} PUBLIC stdc++)

set(ODE_PRECISION "dDOUBLE")
set(CCD_PRECISION "CCD_DOUBLE")
set(ODE_VERSION "Custom-ODE")

configure_file(${BASE}/include/ode/version.h.in ode/version.h)
configure_file(${BASE}/include/ode/precision.h.in ode/precision.h)
configure_file(${BASE}/libccd/src/ccd/precision.h.in ccd/precision.h)
configure_file(config.h.in config.h)
