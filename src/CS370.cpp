// CS370.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "../include/raylib.h"

using namespace std;

int main()
{
	// Create the main window	
	const int screenWidth = 1200;
	const int screenHeight = 800;
	InitWindow(screenWidth, screenHeight, "CS370");

	//init variables
	Texture2D ball = LoadTexture("../assets/cool-sports-ball.png");

    int frameWidth = ball.width;
    int frameHeight = ball.height;

    // Source rectangle (part of the texture to use for drawing)
    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight};

    // Destination rectangle (screen rectangle where drawing part of texture)
    Rectangle destRec = { screenWidth/2.0f, screenHeight/2.0f, frameWidth/2.0f, frameHeight/2.0f };

    // Origin of the texture (rotation/scale point), it's relative to destination rectangle size
    Vector2 origin = { destRec.width/2, destRec.height/2 };

    int rotation = 0;

	// Main game loop
    SetTargetFPS(60);
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{

		// Update
		rotation++;

		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawTexturePro(ball, sourceRec, destRec, origin, (float)rotation, GREEN);

		EndDrawing();
	}
	return 0;
}
