#ifndef COMMONOBJECT_H
#pragma once

#include "Main.h"
#include "CommonMath.h"

struct BoundingBox {
	FloatVector3 tbl, tbr, tfl, tfr, bbl, bbr, bfl, bfr;
	
	bool PointVsBox(FloatVector3 point);
	bool BoxVsBox(BoundingBox box);
};

struct Object {
	FloatVector3 origin;
	BoundingBox box;
	sf::Color colour;
	unsigned char type;
	float radius;
	FloatVector3 normal;
	
	Object();
};

struct Sphere : Object {
	void init(FloatVector3 Origin, float Radius, sf::Color Colour);
	Sphere(FloatVector3 Origin, float Radius, sf::Color Colour);
};

struct Cube : Object {

};

struct Plane : Object {
	void init(FloatVector3 Origin, float Radius,FloatVector3 Normal, sf::Color Color);
	Plane(FloatVector3 Origin, float Radius, FloatVector3 Normal, sf::Color Color);
};
#endif // COMMONOBJECT_H

