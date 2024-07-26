#ifndef COMMONSPLINE_H

#include "Main.h"
#include "CommonStruct.h"

#pragma once
struct SplineArray {
	std::vector<FloatVector2> vertexs;
	FloatVector2 GetSplineVertex(float t);
};

class Spline {
private:
	// Vector to hold vertexs
	SplineArray path;
	void DrawSpline();

public:

	void GeneratePoints(float start, float end, float numOfPoints, float height, float ampitude);
	void Update();

};
#endif // !spline



