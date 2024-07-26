#include "CommonMath.h"
#include "CommonStruct.h"
#include <corecrt_math.h>
#include "Main.h"

float ClampF(float input, float max, float min) {
	if (input > max) {
		input = max;
	}
	else if (input < min) {
		input = min;
	}
	return input;
}

float ReMapF(float input, float inputMax, float inputMin, float newMax, float newMin) {
	return (((input - inputMin) / (inputMax - inputMin)) * newMax) + newMin;
}

FloatVector2 CalculateVertexFromRadian(float radian, float radius, float x, float y ) {
	FloatVector2 vertexPosition;
	vertexPosition.x = cos(radian) * radius + x;
	vertexPosition.y = sin(radian) * radius + y;
	return vertexPosition;
}

float ClampedRandomF(float low, float high) {
	return ReMapF(rand(), 32767, 0, high, low);
}

float DotProduct(FloatVector2 one, FloatVector2 two) {
	return (one.x*two.x) + (one.y*two.y);
}

float DotProduct(FloatVector3 one, FloatVector3 two) {
	return (one.x * two.x) + (one.y * two.y) + (one.z * two.z);
}

float VectorMagnitude(FloatVector2 vector) {
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float VectorMagnitude(FloatVector3 vector) {
	return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

float VectorMagnitudeSqred(FloatVector3 vector) {
	return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
}

FloatVector2 AddVectors(FloatVector2 one, FloatVector2 two) {
	return { (one.x + two.x),(one.y + two.y) };
}

FloatVector3 AddVectors(FloatVector3 one, FloatVector3 two) {
	return { (one.x + two.x),(one.y + two.y),(one.z + two.z)};
}

FloatVector3 VectorDiff(FloatVector3 one, FloatVector3 two) {
	return {(one.x-two.x),(one.y-two.y),(one.z-two.z)};
}

FloatVector3 DivideVector(FloatVector3 vector, float denomonator) {
	return { vector.x / denomonator, vector.y / denomonator, vector.z / denomonator };
}

FloatVector3 InvertVector(FloatVector3 vector) {
	return { -vector.x, -vector.y,-vector.z };
}

FloatVector3 MultiplyVector(FloatVector3 one, FloatVector3 two) {
	return { one.x * two.x,one.y * two.y,one.z * two.z };
}

FloatVector3 MultiplyVector(FloatVector3 vector, float multiplier) {
	return { vector.x * multiplier ,vector.y * multiplier ,vector.z * multiplier };
}

FloatVector3 CrossProduct(FloatVector3 one, FloatVector3 two) {
	if (DotProduct(one, two) != 0) {
		return { one.y * two.z - two.y * one.z, -(one.x * two.z - two.x * one.z), one.x * two.y - two.x * one.y };
	}
}