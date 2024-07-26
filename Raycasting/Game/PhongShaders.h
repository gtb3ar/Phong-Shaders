

#pragma once
#include "PhongShaders.h"
#include "CommonMath.h"
#include "Raycasters.h"
#include "Main.h"
#include "CommonObject.h"

struct Light {
	FloatVector3 origin;
	float range;
	sf::Color color;

	FloatVector3 lightNormal;

	Light(FloatVector3 Origin, float Range, sf::Color Color);

	void SetColor(sf::Color);
};

class PhongShaders
{
private:
	Light* lights;
	float numOfLights;
	float fullLight;
	Object* objects;
	float numOfObjects;

	FloatVector3 camDirection;

public:
	float ambientMultiplier;
	float diffuseStrength;
	sf::Color lightColor;
	float specularThreshold;
	float fresnelStrength;



	PhongShaders(Light* Lights, float NumOfLights, Object* Objects, float numOfObjects);

	void SetLights(Light* Lights, float NumOfLights);

	void SetLightNormals(FloatVector3 vertex);
	void SetCamDirection(FloatVector3 vertex, FloatVector3 camPosition);

	

	sf::Color ScaleColor(sf::Color color, float scale);

	sf::Color GetLighting(sf::Color objectColor, FloatVector3 normal, FloatVector3 vertex, FloatVector3 cameraOrigin);

	sf::Color ApplyAmbient(sf::Color color);

	sf::Color ApplyDiffuse(sf::Color color, FloatVector3 normal, FloatVector3 vertex);

	sf::Color ApplySpecular(sf::Color color, FloatVector3 normal);

	sf::Color ApplyFresnelLens(sf::Color color, FloatVector3 normal, FloatVector3 vertex, FloatVector3 cameraOrigin);
	sf::Color GetLighting(Hit<FloatVector3> hit, FloatVector3 camPosition, int bounces);
	FloatVector3 ReflectAcrossNorm(FloatVector3 lightNorm, FloatVector3 objectNorm);
	//sf::Color ApplySpecular(sf::Color color, float fuckKnows);
};



