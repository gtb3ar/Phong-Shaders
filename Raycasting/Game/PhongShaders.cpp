#include "PhongShaders.h"

PhongShaders::PhongShaders(Light* Lights, float NumOfLights, Object* Objects, float NumOfObjects) {
	ambientMultiplier = 0.1f;
	diffuseStrength = 1;
	specularThreshold = 0.9f;
	lights = Lights;
	lightColor = sf::Color::White;
	fresnelStrength = 0.5;
	numOfLights = NumOfLights;
	fullLight = 1 - ((1 - specularThreshold) * 1 / 3);
	objects = Objects;
	numOfObjects = NumOfObjects;
}

Light::Light(FloatVector3 Origin, float Range, sf::Color Color) {
	origin = Origin;
	range = Range;
	color = Color;
	lightNormal = { 0,0,0 };
}

void PhongShaders::SetLights(Light* Lights, float NumOfLights) {
	lights = Lights;
	numOfLights = NumOfLights;
}

sf::Color PhongShaders::ApplyAmbient(sf::Color color) {
	color.r = color.r * ambientMultiplier;
	color.g = color.g * ambientMultiplier;
	color.b = color.b * ambientMultiplier;
	return color;
}

sf::Color PhongShaders::ApplyDiffuse(sf::Color color, FloatVector3 normal, FloatVector3 vertex) {
	sf::Color runningColor(0,0,0);
	Light* lightPtr = lights;
	for (int currentLight = 0; currentLight < numOfLights; currentLight++) {
		float dot = DotProduct(lightPtr->lightNormal, normal);
		if (dot >= 0) {
			dot = ReMapF(dot, 1, 0, diffuseStrength, 0);
			runningColor = runningColor + (sf::Color(color.r * dot, color.g * dot, color.b * dot) * lightColor);
			
		}
		else {
			runningColor = runningColor + sf::Color(0, 0, 0);
		}
		lightPtr++;
	}
	return runningColor;
}

sf::Color PhongShaders::ApplySpecular(sf::Color color, FloatVector3 normal) {
	sf::Color runningColor(0, 0, 0);

	Light* lightPtr = lights;

	for (int currentLight = 0; currentLight < numOfLights; currentLight++) {

		float dot = DotProduct(ReflectAcrossNorm(lightPtr->lightNormal, normal), camDirection);

		if (dot >= specularThreshold) {
			if  (dot >= fullLight) {
				runningColor = runningColor + lightPtr->color;
			}
			else {
				dot = ReMapF(dot, fullLight, specularThreshold, 1, 0);
				runningColor = runningColor + ScaleColor(lightPtr->color, dot);
			}
		}
		else {
			
			runningColor = runningColor + sf::Color(0, 0, 0);
		}
		lightPtr++;
	}
	return runningColor;

	

}

sf::Color PhongShaders::ApplyFresnelLens(sf::Color color, FloatVector3 normal, FloatVector3 vertex, FloatVector3 cameraOrigin) {
	float dot = DotProduct(InvertVector(camDirection), normal);
	if (dot > -fresnelStrength) {
		dot = ClampF(dot, 0.3, -fresnelStrength);
		dot = ReMapF(dot, 0.3, -fresnelStrength, 1, 0);
		dot = 1 - dot;
		color.r = color.r * dot;
		color.g = color.g * dot;
		color.b = color.b * dot;
		return color;
	}
}

sf::Color PhongShaders::GetLighting(sf::Color objectColor, FloatVector3 normal, FloatVector3 vertex, FloatVector3 cameraOrigin) {
	sf::Color ambient = ApplyAmbient(objectColor);
	sf::Color diffuse = ApplyDiffuse(objectColor, normal, vertex);
	sf::Color specular = ApplySpecular(objectColor, normal);
	sf::Color fresnel = ApplyFresnelLens(sf::Color::Blue, normal, vertex, cameraOrigin);
	return ambient + diffuse + specular + fresnel;
}

void PhongShaders::SetLightNormals(FloatVector3 vertex) {
	Light* lPtr = lights;
	for (int currentLight = 0; currentLight < numOfLights; currentLight++) {
		FloatVector3 LN = VectorDiff(lPtr->origin, vertex);
		(lPtr + currentLight)->lightNormal = DivideVector(LN, VectorMagnitude(LN));
	}
}

void PhongShaders::SetCamDirection(FloatVector3 vertex, FloatVector3 camPosition) {
	FloatVector3 diff = VectorDiff(vertex, camPosition);
	camDirection = DivideVector(diff, VectorMagnitude(diff));
}

sf::Color PhongShaders::GetLighting(Hit<FloatVector3> hit, FloatVector3 camPosition, int bounces) {
	
	if (hit.objectHit->type == 'S' || hit.objectHit->type =='P') { // Sphere lighting
		SetLightNormals(hit.vertex);
		SetCamDirection(hit.vertex, camPosition);

		sf::Color ambient = ApplyAmbient(hit.objectHit->colour);
		sf::Color diffuse = ApplyDiffuse(hit.objectHit->colour, hit.normal, hit.vertex);
		sf::Color specular = ApplySpecular(hit.objectHit->colour, hit.normal);
		sf::Color fresnel = ApplyFresnelLens(sf::Color::Blue, hit.normal, hit.vertex, camPosition);
		sf::Color reflection = sf::Color(0, 0, 0);
		if (bounces > 0) {
			Raycast3D ray(hit.vertex, hit.normal, 4000);
			Hit<FloatVector3> closestHit;
			closestHit.distanceFromOrigin = 5000;
			for (int currentObject = 0; currentObject < numOfObjects; currentObject++) {
				Hit<FloatVector3> hit = ray.DetectObjectCollision(objects + currentObject);
				if (hit.collision == true && hit.distanceFromOrigin < closestHit.distanceFromOrigin) {
					closestHit = hit;
				}
			}

			if (closestHit.distanceFromOrigin != 5000) {
				reflection = ScaleColor(GetLighting(closestHit, camPosition, (bounces - 1)), 1-(1/(bounces+1)));
				float highest = std::max(std::max(diffuse.r, diffuse.g), diffuse.b);
				reflection = ScaleColor(reflection, ReMapF(highest, 255, 0, 1, ambientMultiplier));
				
			}
		}

		return ambient + diffuse + specular + fresnel + reflection;
		
	}
	else {
		return sf::Color(0, 0, 0);
	}



}

sf::Color PhongShaders::ScaleColor(sf::Color color, float scale) {
	return sf::Color(color.r * scale, color.g * scale, color.b * scale);
}

FloatVector3 PhongShaders::ReflectAcrossNorm(FloatVector3 lightNorm, FloatVector3 objectNorm) {
	return VectorDiff(lightNorm, MultiplyVector(objectNorm, DotProduct(lightNorm, objectNorm) * 2));
}

