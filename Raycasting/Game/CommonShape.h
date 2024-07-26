#ifndef COMMONSHAPE_H
#pragma once

#include "CommonStruct.h"
#include "Main.h"

void DrawCircle(float centerX, float centerY, float radius, sf::Color color);
void DrawRectangle(float left, float top, float width, float height, sf::Color color);
void DrawPixel(float x, float y, sf::Color color);
void DrawLine(float x1, float y1, float x2, float y2, sf::Color color);
void DrawLine(FloatVector2 one, FloatVector2 two, sf::Color color);
void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, sf::Color color);

class Polygon {
private:
	float numberOfVertices;
	sf::Color color = sf::Color::White;

	Vertex* vertices;

	virtual FloatVector2 CalculateVertexFromRadian(float radian, float radi) final;
	virtual void DrawPolygon() final;

public:

	FloatVector2 position;
	FloatVector2 scale;
	float rotation;

	virtual void InitPoly(float xPos, float yPos, float xScale, float yScale, float rot, float NOV, Vertex* map) final;
	virtual void Update() final;
	virtual void PosRotUpdate(FloatVector2 pos, float rot) final;
};


class MeshMapStore {
private:

	Vertex* map;
	float numberOfVertices;

public:

	void storeMap(std::vector<FloatVector2> vertexMap);
	Vertex* readMap();
	float getNOV();
};
#endif // !COMMONSHAPE_H



