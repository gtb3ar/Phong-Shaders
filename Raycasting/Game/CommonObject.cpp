#include "CommonObject.h"

bool BoundingBox::PointVsBox(FloatVector3 point) {
	if (point.x > tbl.x && point.y > tbl.y && point.z < tbl.z && point.x < bfr.x && point.y < bfr.y && point.z > bfr.z) {
		return true;
	} 
	return false;
}

bool BoundingBox::BoxVsBox(BoundingBox box) {
	FloatVector3* currentCorner = reinterpret_cast<FloatVector3*>(&box);
	for (int cornerCount = 0; cornerCount < 8; cornerCount++) {
		if (PointVsBox(*(currentCorner))) {
			return true;
		}
		currentCorner++;
	}
	return false;
}

Object::Object() {

}

Sphere::Sphere(FloatVector3 Origin, float Radius, sf::Color Colour) {
	origin = Origin;
	radius = Radius;
	colour = Colour;
	type = 'S';
};

void Sphere::init(FloatVector3 Origin, float Radius, sf::Color Colour) {
	origin = Origin;
	radius = Radius;
	colour = Colour;
	type = 'S';

	box.tbl = { origin.x - radius, origin.y - radius, origin.z + radius };
	box.tbr = { origin.x + radius, origin.y - radius, origin.z + radius };
	box.tfl = { origin.x - radius, origin.y - radius, origin.z - radius };
	box.tfr = { origin.x + radius, origin.y - radius, origin.z - radius };

	box.bbl = { origin.x - radius, origin.y + radius, origin.z + radius };
	box.bbr = { origin.x + radius, origin.y + radius, origin.z + radius };
	box.bfl = { origin.x - radius, origin.y + radius, origin.z - radius };
	box.bfr = { origin.x + radius, origin.y + radius, origin.z - radius };
};

Plane::Plane(FloatVector3 Origin, float Radius, FloatVector3 Normal, sf::Color Color) {
	origin = Origin;
	normal = Normal;
	type = 'P';
	colour = Color;
	radius = Radius;
}

void Plane::init(FloatVector3 Origin, float Radius, FloatVector3 Normal, sf::Color Color) {
	origin = Origin;
	normal = Normal;
	type = 'P';
	colour = Color;
	radius = Radius;
}