#include "Main.h"
#include "CommonStruct.h"
#include "CommonMath.h"
#include "time.h"
#include <stdio.h>
#include "CommonShape.h"
#include "Raycasters.h"
#include "PhongShaders.h"
#include "CommonObject.h"

// Define variables which determine how big the window will be
const float SCREEN_WIDTH = 1200;
const float SCREEN_HEIGHT = 800;

const int PIXEL_BYTES = 3; // RGB
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;

#pragma pack(push,1)
struct StockBitmapHeader {
	// File Header
	uint16_t identifier;
	uint32_t fileSize;
	uint32_t resevedSpace;
	uint32_t offset;

	// Info Header
	uint32_t infoHeaderSize;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint32_t compression;
	uint16_t bitsPerPixel;

	uint32_t imageSize;
	uint32_t XPixelsPerMeter;
	uint32_t YPixelsPerMeter;
	uint32_t usedColours;
	uint32_t importantColours;

	StockBitmapHeader(unsigned int Width, unsigned int Height) {
		// File Header
		identifier = 'MB';
		fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (Width * Height);
		resevedSpace = 0;
		offset = FILE_HEADER_SIZE + INFO_HEADER_SIZE;
		// Info Header - Used
		infoHeaderSize = INFO_HEADER_SIZE;
		width = Width;
		height = Height;
		planes = 1;
		compression = PIXEL_BYTES * 8;
		// Ifno Header - Unused
		bitsPerPixel = 0;
		imageSize = 0;
		XPixelsPerMeter = 0;
		YPixelsPerMeter = 0;
		usedColours = 0;
		importantColours = 0;
	}

};
#pragma pack(pop)

void generateBitmap(unsigned char* imageData, unsigned int width, unsigned int height, char* fileName)
{

	FILE* bmpFile = fopen(fileName, "wb");
	StockBitmapHeader* header = new StockBitmapHeader(width, height);
	fwrite
	(
		reinterpret_cast<unsigned char*>(header),
		1,
		FILE_HEADER_SIZE + INFO_HEADER_SIZE,
		bmpFile
	);
	delete(header);
	for (unsigned int currentWidth = 0; currentWidth < width; currentWidth++) {
		fwrite((imageData + (currentWidth * height * PIXEL_BYTES)), PIXEL_BYTES, height, bmpFile);
	}

	fclose(bmpFile);
}



float pixels = SCREEN_WIDTH * SCREEN_HEIGHT;
FloatVector3 screenCentre = { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0 };
float camDistanceFrontScreen = 800;
FloatVector3 camPosition = {SCREEN_WIDTH/2,SCREEN_HEIGHT/2,-camDistanceFrontScreen};

float numOfBalls = 2;
Object* balls = (Object*)malloc((float)sizeof(Object) * (numOfBalls));

float numOfLights = 1;
Light* lights = (Light*)malloc((float)sizeof(Light) * numOfLights);

Raycast3D renderRay(camPosition, { 0,0,0 }, 6000);

unsigned char* image;

PhongShaders* shader;

// GameInit is called once, when the program starts. Its job is to do things which only happen once, at the start.
void GameInit()
{
	// Create a window for the game
	window = new sf::RenderWindow(sf::VideoMode(static_cast<int>(SCREEN_WIDTH), static_cast<int>(SCREEN_HEIGHT)), "Raycasting");
	
	FloatVector3 diff = VectorDiff({ 0, 0, 0 }, camPosition);
	renderRay.Init(camPosition, DivideVector(diff, VectorMagnitude(diff)), 6000);

	image = reinterpret_cast<unsigned char*>(malloc(sizeof(unsigned char) * SCREEN_HEIGHT * SCREEN_WIDTH * PIXEL_BYTES));

	
	Object* ballPtr = balls;
	((Sphere*)ballPtr)->init({ SCREEN_WIDTH  / 3,SCREEN_HEIGHT / 2, 0 }, 120, sf::Color(255, 125, 0)); ballPtr++;
	((Sphere*)ballPtr)->init({ SCREEN_WIDTH*2 / 3,SCREEN_HEIGHT / 2, 100 }, 120, sf::Color(10, 10, 255));
	
	float current = 0;
	Light* lightPtr = lights;
	current = 0;
	while (current < numOfLights) {
		lightPtr->origin = FloatVector3(SCREEN_WIDTH * (current + 1) / 2, SCREEN_HEIGHT/2, -300);
		lightPtr->color = (sf::Color(255, 255, 0));
		lightPtr++; current++;
	}
	
	shader = new PhongShaders(lights, numOfLights, balls, numOfBalls);

}
float totalTime = 0.0f;		// Total number of seconds since the program started
float cumulative = 0;

unsigned char* GetScreenData(FloatVector3 start, FloatVector3 end) {

	unsigned char* image = reinterpret_cast<unsigned char*>(malloc(sizeof(unsigned char) * (end.x - start.x) * (end.y - start.y) * PIXEL_BYTES));



	for (int currentColumn = start.x; currentColumn < end.x; currentColumn++) {
		for (int currentRow = start.y; currentRow < end.y; currentRow++) {

			Object* tempPtr = balls;
			Hit<FloatVector3> closestHit;
			closestHit.distanceFromOrigin = 10000000000;

			for (int currentBall = 0; currentBall < numOfBalls; currentBall++) {
				FloatVector3 diff = VectorDiff({ (float)currentColumn, (float)currentRow, 0 }, camPosition);
				renderRay.Init(camPosition, DivideVector(diff, VectorMagnitude(diff)), 6000);
				Hit<FloatVector3> hit;
				if (tempPtr->type == 'S') {
					hit = renderRay.DetectShpereCollision(reinterpret_cast<Sphere*>(tempPtr));
					if (closestHit.distanceFromOrigin > hit.distanceFromOrigin) {
						closestHit = hit;
					}
				}
				else if (tempPtr->type == 'P') {
					hit = renderRay.DetectPlaneCollision(reinterpret_cast<Plane*>(tempPtr));
					if (closestHit.distanceFromOrigin > hit.distanceFromOrigin) {
						closestHit = hit;
					}
				}
				tempPtr++;


			}
			int index = (currentColumn - start.x) * ((end.y - start.y) * PIXEL_BYTES) + 
						(currentRow - start.y) * PIXEL_BYTES;
						// Add the pix
						
			sf::Color color = sf::Color::Black;
			if (closestHit.collision == true) {
				color = shader->GetLighting(closestHit, camPosition, 3);
			}
			image[index + 0] = static_cast<unsigned char>(color.b);
			image[index + 1] = static_cast<unsigned char>(color.g);
			image[index + 2] = static_cast<unsigned char>(color.r);



		}
	}


	return image;
}

void MoveLighting(float cumulative) {

	Light* lightPtr = lights;
	float current = 0;
	while (current < numOfLights) {
		lightPtr->origin.x = cos(cumulative * 0.2) * 1000 + SCREEN_WIDTH / 2;
		lightPtr->origin.z = sin(cumulative * 0.2) * 1000 + SCREEN_HEIGHT / 2;
		lightPtr++; current++;
	}

	shader->SetLights(lights, numOfLights);

}

// GameLoop is called repeatedly. Its job is to update the 'game', and draw the screen.
void GameLoop(float elapsedSeconds)
{	
	cumulative = cumulative + elapsedSeconds;
	MoveLighting(cumulative);
	generateBitmap(GetScreenData({0,0,0},{SCREEN_WIDTH,SCREEN_HEIGHT,0}), SCREEN_HEIGHT, SCREEN_WIDTH, (char*)"bitmap.bmp");

	sf::Sprite sprite;

	// Set the position
	sprite.setPosition(SCREEN_WIDTH,0);
	sprite.rotate(90);

	// Set the texture
	sf::Texture bmp;
	bmp.loadFromFile("bitmap.bmp");
	sprite.setTexture(bmp);

	// Draw the sprite
	window->draw(sprite);
}



