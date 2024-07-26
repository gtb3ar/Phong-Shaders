#include "CommonStruct.h"

FloatVector2::FloatVector2(float xInput, float yInput) {
	x = xInput;
	y = yInput;
}

FloatVector2::FloatVector2() {
	x = 0;
	y = 0;
}

FloatVector3::FloatVector3(float X, float Y, float Z) {
	x = X;
	y = Y;
	z = Z;
}

FloatVector3::FloatVector3() {
	x = 0;
	y = 0;
	z = 0;
}

Vertex::Vertex() {
	radian = 0;
	radius = 0;
}