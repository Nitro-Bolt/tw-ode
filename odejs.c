#include <ode/ode.h>

#define MAX_CONTACTS 256

static void near_callback(void* data, dGeomID o1, dGeomID o2){
	dBodyID b1 = dGeomGetBody(o1);
	dBodyID b2 = dGeomGetBody(o2);
	dContact contact[MAX_CONTACTS];
	int i, numc;
	dWorldID world = ((dWorldID*)data)[0];
	dSpaceID space = ((dSpaceID*)data)[1];
	dJointGroupID contactgroup = ((dJointGroupID*)data)[2];

	if(b1 && b2 && dAreConnectedExcluding(b1, b2, dJointTypeContact)) return;

	if(dGeomIsSpace(o1) || dGeomIsSpace(o2)){
		dSpaceCollide2(o1, o2, data, near_callback);
		if(dGeomIsSpace(o1)) dSpaceCollide((dSpaceID)o1, data, near_callback);
		if(dGeomIsSpace(o2)) dSpaceCollide((dSpaceID)o2, data, near_callback);
	}else{
		for(i = 0; i < MAX_CONTACTS; i++){
			contact[i].surface.mode = dContactApprox1;
			contact[i].surface.mu = 2;
		}

		numc = dCollide(o1, o2, MAX_CONTACTS, &contact[0].geom, sizeof(dContact));

		for(i = 0; i < numc; i++){
			dJointID c = dJointCreateContact(world, contactgroup, &contact[i]);
			dJointAttach(c, b1, b2);
		}
	}
}

void dDoCollision(dWorldID world, dSpaceID space, dJointGroupID contactgroup){
	void* args[3];

	args[0] = world;
	args[1] = space;
	args[2] = contactgroup;

	dSpaceCollide(space, (void*)args, near_callback);
}
