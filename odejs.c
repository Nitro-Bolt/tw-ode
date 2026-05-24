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

void dBodyInitMass(dBodyID body, double mass) {
        dMass m, mt;
        dGeomID g;

        dMassSetZero(&m);

        for(g = dBodyGetFirstGeom(body); g != 0; g = dBodyGetNextGeom(g)){
                int c = dGeomGetClass(g);

                dMassSetZero(&mt);

                if(c == dSphereClass){
                        dMassSetSphereTotal(&mt, mass, dGeomSphereGetRadius(g));
                }else if(c == dBoxClass){
                        dVector3 v;

                        dGeomBoxGetLengths(g, v);

                        dMassSetBoxTotal(&mt, mass, v[0], v[1], v[2]);
                }else if(c == dTriMeshClass){
                        dMassSetTrimesh(&mt, mass, g);
                }

                dMassAdd(&m, &mt);
        }

        if(m.mass == 0) return;

        dMassAdjust(&m, mass);
        dBodySetMass(body, &m);
}

static void ray_callback(void* data, dGeomID geom1, dGeomID geom2){
	dReal* hit = data;
	dContact contacts[MAX_CONTACTS];
	int count = dCollide(geom1, geom2, MAX_CONTACTS, &contacts[0].geom, sizeof(dContact));
	int i;

	for(i = 0; i < count; i++){
		if(contacts[i].geom.depth < hit[3]){
			dCopyVector3(hit, contacts[i].geom.pos);
			hit[3] = contacts[i].geom.depth;
		}
	}
}

int dRaycast(dSpaceID space, dReal sx, dReal sy, dReal sz, dReal ex, dReal ey, dReal ez){
	dVector3 start, end, dir;
	dReal length, ilength;
	dGeomID ray;
	dVector4 hit;

	start[0] = sx, start[1] = sy, start[2] = sz;
	end[0] = ex, end[1] = ey, end[2] = ez;

	dSubtractVectors3(dir, end, start);

	length = dCalcVectorLength3(dir);
	ilength = dRecip(length);

	dScaleVector3(dir, ilength);

	ray = dCreateRay(0, length);
	dGeomRaySet(ray, sx, sy, sz, dir[0], dir[1], dir[2]);

	hit[3] = dInfinity;

	dSpaceCollide2(ray, (dGeomID)space, hit, ray_callback);

	dGeomDestroy(ray);

	if(hit[3] != dInfinity){
		return 1;
	}

	return 0;
}

struct ray_geom_data {
	dVector4 hit;
	dGeomID geom;
};

static void ray_callback_geom(void* data, dGeomID geom1, dGeomID geom2){
	struct ray_geom_data* r = data;
	dContact contacts[MAX_CONTACTS];
	int count = dCollide(geom1, geom2, MAX_CONTACTS, &contacts[0].geom, sizeof(dContact));
	int i;

	for(i = 0; i < count; i++){
		if((contacts[i].geom.g1 == r->geom || contacts[i].geom.g2 == r->geom) && contacts[i].geom.depth < r->hit[3]){
			dCopyVector3(r->hit, contacts[i].geom.pos);
			r->hit[3] = contacts[i].geom.depth;
		}
	}
}

int dRaycastGeom(dSpaceID space, dReal sx, dReal sy, dReal sz, dReal ex, dReal ey, dReal ez, dGeomID geom){
	dVector3 start, end, dir;
	dReal length, ilength;
	dGeomID ray;
	struct ray_geom_data r;

	start[0] = sx, start[1] = sy, start[2] = sz;
	end[0] = ex, end[1] = ey, end[2] = ez;

	dSubtractVectors3(dir, end, start);

	length = dCalcVectorLength3(dir);
	ilength = dRecip(length);

	dScaleVector3(dir, ilength);

	ray = dCreateRay(0, length);
	dGeomRaySet(ray, sx, sy, sz, dir[0], dir[1], dir[2]);

	r.hit[3] = dInfinity;
	r.geom = geom;

	dSpaceCollide2(ray, (dGeomID)space, &r, ray_callback);

	dGeomDestroy(ray);

	if(r.hit[3] != dInfinity){
		return 1;
	}

	return 0;
}
