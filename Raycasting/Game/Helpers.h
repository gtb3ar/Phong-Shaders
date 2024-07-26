#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

// Drawing
void DrawString(std::string text, float x, float y, int height, sf::Color color);
void DrawTexture(float x, float y, sf::Texture texture);
void DrawTexture(float x, float y, float width, float height, sf::Texture texture);
void DrawRotatedTexture(float centerX, float centerY, float width, float height, float rotationDegrees, sf::Texture texture);

// Keyboard and mouse input
bool IsKeyPressed(sf::Keyboard::Key key);
bool IsMouseButtonPressed();
int GetMouseX();
int GetMouseY();

// Audio
sf::Sound LoadSound(const char* filePath);
void PlayMusic(const char* filePath);
void StopMusic();

// Misc
// This replaces the standard 'printf' function with one which outputs
// to the Visual Studio output window.
#define printf printf2
int __cdecl printf2(const char* format, ...);
