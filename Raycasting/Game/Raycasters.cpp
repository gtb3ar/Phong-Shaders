#include "Raycasters.h"

	Raycast2D::Raycast2D(FloatVector2 Origin, FloatVector2 Direction, float MaxDistance) {
		origin = Origin;
		direction = Direction;
		distance = MaxDistance;
		hit.collision = false;
	}

	Hit<FloatVector3> Raycast3D::DetectBoxCollision(BoundingBox box) {
		Hit<FloatVector3> tep;
		return tep;
	}

	Hit<FloatVector2> Raycast2D::DetectShpereCollision(FloatVector2 sphereOrigin, float sphereRadius) {
		FloatVector2 originToSphere;
		originToSphere.x = sphereOrigin.x - origin.x;
		originToSphere.y = sphereOrigin.y - origin.y;

		float dot = DotProduct(direction, originToSphere);

		float distanceSphereAngle = acos(dot / (abs(VectorMagnitude(direction)) * abs(VectorMagnitude(originToSphere))));

		float sphereToDistanceMagnitude = sqrt(VectorMagnitude(originToSphere) * VectorMagnitude(originToSphere) - dot * dot);

		if (sphereToDistanceMagnitude <= sphereRadius) { // Collision
			hit.distanceFromOrigin = dot - sqrt(sphereRadius * sphereRadius - sphereToDistanceMagnitude * sphereToDistanceMagnitude);
			if (hit.distanceFromOrigin <= distance) {
				hit.vertex = AddVectors(origin, { direction.x * hit.distanceFromOrigin, direction.y * hit.distanceFromOrigin });
				hit.collision = true;
			}
			else {
				hit.distanceFromOrigin = distance;
				hit.vertex = AddVectors(origin, { direction.x * hit.distanceFromOrigin, direction.y * hit.distanceFromOrigin });
				hit.collision = false;
			}


			return hit;
		}

		hit.distanceFromOrigin = distance;
		hit.vertex = AddVectors(origin, { direction.x * hit.distanceFromOrigin, direction.y * hit.distanceFromOrigin });
		hit.collision = false;

		return hit;
	}

	FloatVector2 Raycast2D::getDirectionVector() {
		return { direction.x * hit.distanceFromOrigin,direction.y * hit.distanceFromOrigin };
	}

	FloatVector2 Raycast2D::getOrigin() {
		return origin;
	}

	void Raycast2D::setOrigin(FloatVector2 newOrigin) {
		origin = newOrigin;
	}



	Raycast3D::Raycast3D(FloatVector3 Origin, FloatVector3 Direction, float MaxDistance) {
		origin = Origin;
		direction = Direction;
		distance = MaxDistance;
		hit.collision = false;
	}

	void Raycast3D::Init(FloatVector3 Origin, FloatVector3 Direction, float MaxDistance) {
		origin = Origin;
		direction = Direction;
		distance = MaxDistance;
		hit.collision = false;
	}

	Hit<FloatVector3> Raycast3D::DetectShpereCollision(Sphere* sphere) {
		FloatVector3 originToSphere;
		originToSphere.x = sphere->origin.x - origin.x;
		originToSphere.y = sphere->origin.y - origin.y;
		originToSphere.z = sphere->origin.z - origin.z;

		float dot = DotProduct(direction, originToSphere);

		float distanceSphereAngle = acos(dot*dot / (abs(VectorMagnitudeSqred(direction)) * abs(VectorMagnitudeSqred(originToSphere))));

		float sphereToDistanceMagnitude = VectorMagnitude(originToSphere) * VectorMagnitude(originToSphere) - dot * dot;

		if (dot < 0 || distanceSphereAngle < 0 || (sphereToDistanceMagnitude == 0 && distanceSphereAngle != 0)) {
			hit.distanceFromOrigin = distance;
			hit.vertex = AddVectors(origin, { direction.x * hit.distanceFromOrigin, direction.y * hit.distanceFromOrigin, direction.z * hit.distanceFromOrigin });
			hit.objectHit = nullptr;
			hit.collision = false;
			return hit;
		}


		if (sphereToDistanceMagnitude <= sphere->radius * sphere->radius) { // Collision
			hit.distanceFromOrigin = dot - sqrt(sphere->radius * sphere->radius - sphereToDistanceMagnitude);
			if (hit.distanceFromOrigin <= distance) {
				hit.vertex = AddVectors(origin, { direction.x * hit.distanceFromOrigin, direction.y * hit.distanceFromOrigin, direction.z * hit.distanceFromOrigin });
				hit.objectHit = sphere;
				FloatVector3 diff = VectorDiff(sphere->origin, hit.vertex);
				hit.normal = DivideVector(InvertVector(diff), VectorMagnitude(diff));
				hit.collision = true;
			}
			else {
				hit.distanceFromOrigin = distance;
				hit.objectHit = nullptr;
				hit.vertex = AddVectors(origin, { direction.x * hit.distanceFromOrigin, direction.y * hit.distanceFromOrigin, direction.z * hit.distanceFromOrigin });
				hit.collision = false;
			}


			return hit;
		}

		hit.distanceFromOrigin = distance;
		hit.vertex = AddVectors(origin, { direction.x * hit.distanceFromOrigin, direction.y * hit.distanceFromOrigin, direction.z * hit.distanceFromOrigin });
		hit.objectHit = nullptr;
		hit.collision = false;

		return hit;
	}

	Hit<FloatVector3> Raycast3D::DetectPlaneCollision(Plane* plane) {

		float demononator = DotProduct(plane->normal, direction);

		

		if (demononator < 0) {

			FloatVector3 rayToPlane = VectorDiff(plane->origin, origin);

			float hitDistance = DotProduct(rayToPlane, plane->normal) / demononator;
			hit.vertex = MultiplyVector(direction, hitDistance);
			if (plane->radius >= VectorMagnitude(VectorDiff(hit.vertex, plane->origin))) {
				hit.collision = true;
				hit.distanceFromOrigin = hitDistance;
				hit.normal = plane->normal;
				hit.objectHit = plane;
			}
			else {
				hit.collision = false;
			}
			return hit;
		}
		else {
			hit.collision = false;
			return hit;
		}		
		
	}

	Hit<FloatVector3> Raycast3D::DetectObjectCollision(Object* object) {
		switch (object->type) {
		case 'S':
			return DetectShpereCollision((Sphere*)object);
		case 'P':
			return DetectPlaneCollision((Plane*)object);
		}
	}

	FloatVector3 Raycast3D::getDirectionVector() {
		return { direction.x * hit.distanceFromOrigin,direction.y * hit.distanceFromOrigin , direction.z * hit.distanceFromOrigin };
	}

	FloatVector3 Raycast3D::getOrigin() {
		return origin;
	}

	void Raycast3D::setOrigin(FloatVector3 newOrigin) {
		origin = newOrigin;
	}
