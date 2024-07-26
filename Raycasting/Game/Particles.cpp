#include "Particles.h"
#include "CommonStruct.h"
#include "CommonMath.h"
#include "CommonShape.h"
#include "Main.h"


	void Particle::CalculateNewPosition() {
		velocity.x = ReMapF(ClampF(lifeTime - clock.getElapsedTime().asSeconds(),lifeTime,0), lifeTime, 0, originalVelocity.x, 0);
		velocity.y = ReMapF(ClampF(lifeTime - clock.getElapsedTime().asSeconds(),lifeTime, 0), lifeTime, 0, originalVelocity.y, 0);
		if (velocity.x == 0 && velocity.y == 0) {
			live = false;
		}
		position = { position.x + velocity.x,position.y + velocity.y };
	}

	void Particle::Init(float originX, float originY, float scale, FloatVector2 velo, float lifetime, Vertex* map, float numberOfPoints) {
		InitPoly(originX, originY, scale, scale, 0, numberOfPoints, map);
		velocity = {0,0};
		originalVelocity = velo;
		lifeTime = lifetime;
		clock.restart();
		live = false;
	}

	void Particle::UpdateParticle() {
		if (live) {
			CalculateNewPosition();
			Update();
		}
	}

	void Particle::ResetParticle(FloatVector2 pos, FloatVector2 velo) {
		position = pos;
		originalVelocity = { 0,0 };
		originalVelocity = velo;
		clock.restart();
		live = true;
	}



	void ParticleSystem::Init(FloatVector2 pos, float rad, float pps, float lt, std::vector<FloatVector2> vertexMap, float targetvelocity, float velocityveriance, float velocityangleveriance) {
		alive = 0;
		on = false;
		maxParticles = pps * lt;
		particlesPerSecond = pps;
		particleArray = (Particle*)(malloc((size_t)(maxParticles+1) * sizeof(Particle)));
		particleMap.storeMap(vertexMap);
		clock.restart();
		targetVelocity = targetvelocity;
		velocityAngleVeriance = velocityangleveriance;
		velocityVeriance = velocityveriance;
		if (!particleArray == NULL) {
			for (int currentParticle = 0; currentParticle < maxParticles; currentParticle++) {
				particleArray[currentParticle].Init(pos.x,pos.y, 1, CalculateVertexFromRadian(rad + (1.5f - velocityAngleVeriance) + (ClampedRandomF(0, velocityAngleVeriance * 2))
					, ClampedRandomF(targetVelocity-velocityVeriance, targetVelocity + velocityVeriance),0,0), 2, particleMap.readMap(), particleMap.getNOV());
			}
		}


	}

	void ParticleSystem::Update(FloatVector2 pos, float rad) {
		if (on) {
			float particlesNumber = static_cast<float>(clock.getElapsedTime().asSeconds() * particlesPerSecond);
			for (int currentParticle = static_cast<int>(alive); currentParticle < alive + particlesNumber; currentParticle++) {
				if (currentParticle > maxParticles) {
					currentParticle = static_cast<int>(currentParticle - (maxParticles - 1));
					particleArray[currentParticle].ResetParticle(pos, CalculateVertexFromRadian(rad + (1.5f - velocityAngleVeriance) + (ClampedRandomF(0, velocityAngleVeriance * 2))
						, ClampedRandomF(targetVelocity - velocityVeriance, targetVelocity + velocityVeriance), 0, 0));
					break;
				}

				particleArray[currentParticle].ResetParticle(pos, CalculateVertexFromRadian(rad + (1.5f - velocityAngleVeriance) + (ClampedRandomF(0, velocityAngleVeriance * 2))
					, ClampedRandomF(targetVelocity - velocityVeriance, targetVelocity + velocityVeriance), 0, 0));

			}
			alive = alive + particlesNumber;
			clock.restart();
			if (alive > maxParticles) {
				alive = alive - maxParticles;
			}
		}
		for (int currentParticle = 0; currentParticle < maxParticles; currentParticle++) {
			particleArray[currentParticle].UpdateParticle();
		}
		
	}
