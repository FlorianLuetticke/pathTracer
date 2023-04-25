A Pathtracer.



For pathtracing:

A camera shoots a ray of light into a scene. In the Scene it hits an object and returns the colour and light it encounters. We can estimate how much the object is iluminated at that point by sending another ray from the hitpoint into the scene (random, with it's position weighted.) We continue this for N iterations or until we find no object or a "black" object (which can be a light).


A Primitive is a form (sphere, triangle etc.) which can be hit by a ray.
A Primitive contains it's material, coordinates etc.
It creates a HitInfo containing the material/hit position/ normals.

A Material is a class which describes how a primitive scatters/reflects/emits light. Using an incomming ray it can create an outgoing ray to sample the Scene. With the light information returned from that ray it can calculate the light emitted by the material using a BRDF 