#include "CommonSpline.h"
#include "CommonMath.h"
#include "CommonStruct.h"
#include "CommonShape.h"
#include "Main.h"


	FloatVector2 SplineArray::GetSplineVertex(float t) {
		int p0, p1, p2, p3;
		p1 = (int)t + 1;
		p2 = p1 + 1;
		p3 = p2 + 1;
		p0 = p1 - 1;

		t = t - (int)t;

		float tt = t * t;
		float ttt = t * t * t;

		float q1 = -ttt + 2.0f * tt - t;
		float q2 = 3.0f * ttt - 5.0f * tt + 2.0f;
		float q3 = -3.0f * ttt + 4.0f * tt + t;
		float q4 = ttt - tt;

		float tx = 0.5f * (vertexs[p0].x * q1 + vertexs[p1].x * q2 + vertexs[p2].x * q3 + vertexs[p3].x * q4);
		float ty = 0.5f * (vertexs[p0].y * q1 + vertexs[p1].y * q2 + vertexs[p2].y * q3 + vertexs[p3].y * q4);
		return { tx,ty };
	}



	void Spline::DrawSpline() { // Extrapolates between the control points, drawing lines from point to point.
		for (float t = 0.0f; t < (float)path.vertexs.size() - 3.0f; t += 0.05f) {
			FloatVector2 vertex = path.GetSplineVertex(t);
			FloatVector2 nextVertex;
			if (t + 0.05f < (float)path.vertexs.size() - 3.0f) {
				nextVertex = path.GetSplineVertex(t + 0.05f);
			}
			else {
				nextVertex = vertex;
			}
			DrawLine(vertex.x, vertex.y, nextVertex.x, nextVertex.y, sf::Color::White);
		}
	}

	void Spline::GeneratePoints(float start, float end, float numOfPoints, float height, float ampitude) { // Generate the control points
		path.vertexs.clear();
		path.vertexs.push_back({ start,height });
		float increment = (end - start) / (numOfPoints + 1);
		int lBound = static_cast<int>(height - ampitude);
		int uBound = static_cast<int>(height + ampitude);
		srand((unsigned int)time(NULL));
		for (float current = start + increment; current < end; current = current + increment) {
			path.vertexs.push_back({ current, (rand() % (uBound - lBound + 1)) + (float)lBound });
		}
		path.vertexs.push_back({ end,height });
	}


	void Spline::Update() {
		DrawSpline();
	}

