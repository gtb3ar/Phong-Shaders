#ifndef PARTICLES_H
#pragma once

#include "CommonStruct.h"
#include "CommonShape.h"
#include "Main.h"

class Particle : Polygon {
private:

	FloatVector2 originalPosition;
	FloatVector2 velocity;
	FloatVector2 originalVelocity;
	float lifeTime;
	sf::Clock clock;

	void CalculateNewPosition();

public:

	bool live;

	void Init(float originX, float originY, float scale, FloatVector2 velo, float lifetime, Vertex* map, float numberOfPoints);
	void UpdateParticle();
	void ResetParticle(FloatVector2 pos, FloatVector2 velo);
};


class ParticleSystem {
private:
	MeshMapStore particleMap;
	Particle* particleArray;
	float maxParticles = 0;
	float particlesPerSecond;
	sf::Clock clock;
	float alive;
	float targetVelocity;
	float velocityAngleVeriance;
	float velocityVeriance;
	

public:
	bool on;

	void Init(FloatVector2 pos, float rad, float pps, float lt, std::vector<FloatVector2> vertexMap, float targetvelocity, float velocityveriance, float velocityangleveriance);
	void Update(FloatVector2 position, float rad);

};
#endif // !PARTICLES_H
