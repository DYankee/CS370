// CS370.cpp
// CS370.cpp
#include <iostream>
#include "../include/raylib.h"
#include "../include/entt.hpp"

// Include RayTMX in C linkage
extern "C" {
    #define RAYTMX_IMPLEMENTATION
    #include "../include/raytmx.h"
}

using namespace std;

int main()
{
	// Create the main window	
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	InitWindow(screenWidth, screenHeight, "CS370");
//	ToggleFullscreen();

	
	//init variables

	 // Box properties
    Vector2 boxPosition = {400, 300};   // Start in middle
    Vector2 boxSize = {50, 50};         // Width & height
    float speed = 400.0f;               // Pixels per second
	Rectangle box = {boxPosition.x, boxPosition.y, boxSize.x, boxSize.y};

	// platform test
	Rectangle platform1 = {screenWidth/3, screenHeight/2, 300, 50};



	/* ball
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
	*/

    // Main game loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime(); // Time since last frame
		// Update velocity based on gravity
        boxVel.y += GRAVITY * dt;

		// Move box based on key input
		if (IsKeyDown(KEY_D)) box.x += speed * dt;
		if (IsKeyDown(KEY_A)) box.x -= speed * dt;
		if (IsKeyDown(KEY_W)) box.y -= speed * dt;
		if (IsKeyDown(KEY_S)) box.y += speed * dt;

		// Constrain box to stay within screen bounds
		if (box.x < 0) box.x = 0;
		if (box.y < 0) box.y = 0;
		if (box.x > screenWidth - boxSize.x) box.x = screenWidth - boxSize.x;
		if (box.y > screenHeight - boxSize.y) box.y = screenHeight - boxSize.y;

		// Update
		//rotation++;

		BeginDrawing();

		ClearBackground(RAYWHITE);

		
		//DrawRectangleV(boxPosition, boxSize, BLUE); // Draw the box
		DrawRectangleRec(box, BLUE);


		DrawRectangleRec(platform1, BLACK); // Draw test platform

		if (CheckCollisionRecs(box, platform1)) {
			cout << "Collision!" << endl;
		}


         DrawText("Move with W A S D", 10, 10, 20, BLACK);
		//DrawTexturePro(ball, sourceRec, destRec, origin, (float)rotation, GREEN);

        EndDrawing();
    }
    // Cleanup
    UnloadTexture(cowR);
    UnloadTexture(cowL);
    UnloadTMX(map);
    CloseWindow();

    return 0;
}