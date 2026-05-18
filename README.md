# ODE for TurboWarp/NitroBolt

Run `ode.js` or `ode.offline.js` in unsandboxed mode and you should be able to use ODE

It'd be more useful if you combine it with like [three.js extension](https://github.com/Brackets-Coder/ThreeJS-Extension/tree/Nitrobolt-arrays/civero), unless you really just want to simulate physics.

https://github.com/user-attachments/assets/e744a8f0-e60e-4076-9d10-90763a52c94e

## Notes

### World/Space

In ODE you have to create them separately, but in this extension `new world` will create world and space at same time.

### Coordinate system

By default this extension converts `+Y = up` coordinates to ODE (`+Z = up`) coordinates. You can change this behavior by using `change up direction to ...` block.

## Things you might find useful

Maybe these would be useful if you're using ODE for first time.

### Difference between body and geometry

Body is for rigid body physics (like movemenet, gravity, and etc.), and geometry is for collision.

Which means if you want an object that never moves but has collision, you'd only make geometry.

### How you should create an object

1. Create a geometry
2. Create a body
3. Associate the body you created with the geometry you created
4. (optional) Move or rotate body (or geometry)

You **MUST** move or rotate after associating the body with geometry, otherwise object would not move to the position (or get rotated).

## TODO

 - [ ] Add joint stuffs
 - [ ] Add force stuffs
 - [ ] Add ray (and raycast)
 - [ ] Add gravity function
 - [ ] Add mass stuffs
 - [ ] Add trimesh
 - [ ] Add heightfield
 - [ ] Add convex? (Not well documented, so maybe not...)
