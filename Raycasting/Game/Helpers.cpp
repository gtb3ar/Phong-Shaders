#include "Helpers.h"
#include "Main.h"
#include <cstdarg>
#include <stdio.h>
#include <Windows.h>

/////////////////////////////////////////////////////////////////////////////
// DRAWING


void DrawString(std::string myString, float x, float y, int height, sf::Color color)
{
    sf::Text text;

    // Set the text position
    text.setPosition(x, y);

    // Select the font
    text.setFont(defaultFont); // font is a sf::Font

    // Set the string to display
    text.setString(myString);

    // Set the character size (in pixels)
    text.setCharacterSize(height);

    // Set the color
    text.setFillColor(color);

    // Set the text style
    text.setStyle(sf::Text::Bold);

    // Draw the text
    window->draw(text);
}

void DrawTexture(float x, float y, sf::Texture texture)
{
    // Create a sprite object
    sf::Sprite sprite;

    // Set the position
    sprite.setPosition(x, y);

    // Set the texture
    sprite.setTexture(texture);

    // Draw the sprite
    window->draw(sprite);
}

void DrawTexture(float x, float y, float width, float height, sf::Texture texture)
{
    // Create a sprite object
    sf::Sprite sprite;

    // Set the position
    sprite.setPosition(x, y);

    // Set the texture
    sprite.setTexture(texture);

    // Set sprite scale, which is calculated from texture size and desired draw size
    sf::Vector2u textureSize = texture.getSize();
    float xScale = width / textureSize.x;
    float yScale = height / textureSize.y;
    sprite.setScale(xScale, yScale);

    // Draw the sprite
    window->draw(sprite);
}

void DrawRotatedTexture(float centerX, float centerY, float width, float height, float rotationDegrees, sf::Texture texture)
{
    // Create a sprite object
    sf::Sprite sprite;

    // Set sprite scale, which is calculated from texture size and desired draw size
    sf::Vector2u textureSize = texture.getSize();
    float xScale = width / textureSize.x;
    float yScale = height / textureSize.y;
    sprite.setScale(xScale, yScale);

    // Set the position
    sprite.setPosition(centerX, centerY);

    // Set the 'origin' of the texture
    sprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);

    // Set the rotation
    sprite.setRotation(rotationDegrees);

    // Set the texture
    sprite.setTexture(texture);

    // Draw the sprite
    window->draw(sprite);
}

/////////////////////////////////////////////////////////////////////////////
// KEYBOARD AND MOUSE INPUT

#pragma warning(suppress : 26812)   // Stop the compiler complaining about how SFML defines keys
bool IsKeyPressed(sf::Keyboard::Key key)
{
    return sf::Keyboard::isKeyPressed(key);
}
#pragma warning(disable : 26812)   // Allow the compiler to complain again

bool IsMouseButtonPressed()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

int GetMouseX()
{
    // Get mouse position, relative to the window
    sf::Vector2i position = sf::Mouse::getPosition(*window);
    return position.x;
}

int GetMouseY()
{
    // Get mouse position, relative to the window
    sf::Vector2i position = sf::Mouse::getPosition(*window);
    return position.y;
}


/////////////////////////////////////////////////////////////////////////////
// AUDIO

// Variables for 'in memory' sound effects
const int MAX_SOUNDS = 32;
int numLoadedSounds = 0;
sf::SoundBuffer soundBuffers[MAX_SOUNDS];

// Variables for music
sf::Music music;

sf::Sound LoadSound(const char* filePath)
{
    // If we've already used all the slots, return an empty sound object
    sf::Sound sound;
    if (numLoadedSounds >= MAX_SOUNDS - 1)
    {
        return sound;
    }

    // Load the audio file into the next sound buffer in the array
    soundBuffers[numLoadedSounds].loadFromFile(filePath);

    // Make our sound player object use the sound buffer
    sound.setBuffer(soundBuffers[numLoadedSounds]);

    // Increase the counter of how many sounds we've loaded
    numLoadedSounds++;

    // Return the sound player
    return sound;
}

void PlayMusic(const char* filePath)
{
    // Attempt to load the music
    if (!music.openFromFile(filePath))
        return; // error

    // Make it loop
    music.setLoop(true);

    // Start playing
    music.play();
}

void StopMusic()
{
    music.stop();
}


/////////////////////////////////////////////////////////////////////////////
// MISC

// This function gets called when you call printf
// It prints text to the output window in Visual Studio
// This function uses some advanced features of the language, so don't worry
// about understanding it :)
int __cdecl printf2(const char* format, ...)
{
    // Create temporary storage for the text
    char str[1024];

    // Build the text into str
    va_list argptr;
    va_start(argptr, format);
    int ret = vsnprintf(str, sizeof(str), format, argptr);
    va_end(argptr);

    // Print the string to Visual Studio
    OutputDebugStringA(str);

    return ret;
}
