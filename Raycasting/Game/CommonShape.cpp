#include "CommonShape.h"
#include "CommonStruct.h"
#include "CommonMath.h"
#include "Main.h"
#include <stdio.h>

void DrawCircle(float centerX, float centerY, float radius, sf::Color color)
{
	// Create a circle object
	sf::CircleShape myCircle(radius);

	// Set the top left position by subracting the radius from the center position
	float left = centerX - radius;
	float top = centerY - radius;
	myCircle.setPosition(left, top);

	// Set the color
	myCircle.setFillColor(color);

	// Draw it
	window->draw(myCircle);
}

void DrawRectangle(float left, float top, float width, float height, sf::Color color)
{
	// Create a rectangle object
	sf::RectangleShape rectangle(sf::Vector2f(width, height));

	// Set the top left position
	rectangle.setPosition(left, top);

	// Set the color
	rectangle.setFillColor(color);

	// Draw it
	window->draw(rectangle);
}

void DrawPixel(float x, float y, sf::Color color)
{
	// Draw a 1x1 rectangle, using the DrawRectangle function above
	sf::RectangleShape rectangle(sf::Vector2f(1, 1));

	// Set the top left position
	rectangle.setPosition(x, y);

	// Set the color
	rectangle.setFillColor(color);

	// Draw it
	window->draw(rectangle);
	
}

void DrawLine(float x1, float y1, float x2, float y2, sf::Color color)
{
	// Make an array of the two end points (an array is like a list)
	sf::Vertex points[] =
	{
		sf::Vertex(sf::Vector2f(x1, y1)),
		sf::Vertex(sf::Vector2f(x2, y2))
	};

	// Set the color of the points
	points[0].color = color;
	points[1].color = color;

	// Draw the line made by the two end points
	window->draw(points, 2, sf::Lines);
}

void DrawLine(FloatVector2 one, FloatVector2 two, sf::Color color)
{
	// Make an array of the two end points (an array is like a list)
	sf::Vertex points[] =
	{
		sf::Vertex(sf::Vector2f(one.x, one.y)),
		sf::Vertex(sf::Vector2f(one.x, two.y))
	};

	// Set the color of the points
	points[0].color = color;
	points[1].color = color;

	// Draw the line made by the two end points
	window->draw(points, 2, sf::Lines);
}

void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, sf::Color color)
{
	// Create an empty convex shape
	sf::ConvexShape convex;

	// Resize it to 3 points
	convex.setPointCount(3);

	// Define the points
	convex.setPoint(0, sf::Vector2f(x1, y1));
	convex.setPoint(1, sf::Vector2f(x2, y2));
	convex.setPoint(2, sf::Vector2f(x3, y3));

	// Set color
	convex.setFillColor(color);

	// Draw the line made by the two end points
	window->draw(convex);
}


	FloatVector2 Polygon::CalculateVertexFromRadian(float radian, float radi) {
		FloatVector2 vertexPosition;
		vertexPosition.x = cos(radian) * radi * scale.x + position.x;
		vertexPosition.y = sin(radian) * radi * scale.y + position.y;
		return vertexPosition;
	}

	void Polygon::DrawPolygon() {
		//Dot to Dot, connecting the vertex with lines
		for (int point = 0; point < numberOfVertices; point++) {
			int nextPoint = point + 1;
			if (nextPoint == numberOfVertices) {
				nextPoint = 0;
			}
			FloatVector2 vertex = CalculateVertexFromRadian(vertices[point].radian + rotation, vertices[point].radius);
			FloatVector2 nextVertex = CalculateVertexFromRadian(vertices[nextPoint].radian + rotation, vertices[nextPoint].radius);
			printf("now %f:x %f:y\nnext %f:x %f:y\n", vertex.x, vertex.y, nextVertex.x, nextVertex.y);
			DrawLine(vertex.x, vertex.y, nextVertex.x, nextVertex.y, color);
		}
	}

	void Polygon::InitPoly(float xPos, float yPos, float xScale, float yScale, float rot, float NOV, Vertex* map) {
		position.x = xPos;
		position.y = yPos;
		rotation = rot;
		scale.x = xScale;
		scale.y = yScale;
		numberOfVertices = NOV;
		vertices = map;
	}

	void Polygon::Update() {
		DrawPolygon();
	}

	void Polygon::PosRotUpdate(FloatVector2 pos, float rot) {
		position = pos;
		rotation = rot;
		DrawPolygon();
	}


		void MeshMapStore::storeMap(std::vector<FloatVector2> vertexMap) {
			numberOfVertices = (float)vertexMap.size();
			Vertex* vertices = (Vertex*)malloc(numberOfVertices * sizeof(Vertex));
			if (!vertices == NULL) {
				for (int vert = 0; vert < vertexMap.size(); vert++) {
					float y = vertexMap[vert].x;
					float x = vertexMap[vert].y;
					Vertex store;
					store.radian = atan2(x, y);
					store.radius = sqrt(abs(x) * abs(x) + abs(y) * abs(y));
					vertices[vert] = store;
				}
				map = vertices;
			}
		}

		Vertex* MeshMapStore::readMap() {
			return map;
		}

		float MeshMapStore::getNOV() {
			return numberOfVertices;
		}