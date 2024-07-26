#ifndef RAYCASTERS_H
#pragma once

#include "Raycasters.h"
#include "Main.h"
#include "CommonStruct.h"
#include "CommonShape.h"
#include "CommonMath.h"
#include "CommonObject.h"

template<typename Vector>
struct Hit {
	bool collision;
	Vector vertex;
	float distanceFromOrigin;
	Object* objectHit;
	Vector normal;
};

class Raycast2D {
private:
	FloatVector2 origin;
	FloatVector2 direction;
	float distance;
	Hit<FloatVector2> hit;
public:
	Raycast2D(FloatVector2 Origin, FloatVector2 Direction, float MaxDistance);
	Hit<FloatVector2> DetectShpereCollision(FloatVector2 sphereOrigin, float sphereRadius);
	FloatVector2 getDirectionVector();
	FloatVector2 getOrigin();
	void setOrigin(FloatVector2 newOrigin);
};

class Raycast3D {
private:
	FloatVector3 origin;
	FloatVector3 direction;
	float distance;
	Hit<FloatVector3> hit;
public:
	Hit<FloatVector3> DetectBoxCollision(BoundingBox box);
	Hit<FloatVector3> DetectObjectCollision(Object* object);
	Raycast3D(FloatVector3 Origin, FloatVector3 Direction, float MaxDistance);
	void Init(FloatVector3 Origin, FloatVector3 Direction, float MaxDistance);
	Hit<FloatVector3> DetectShpereCollision(Sphere* sphere);
	Hit<FloatVector3> DetectPlaneCollision(Plane* plane);
	FloatVector3 getDirectionVector();
	FloatVector3 getOrigin();
	void setOrigin(FloatVector3 newOrigin);
};

#endif


