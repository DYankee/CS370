// CS370.cpp
#include <iostream>
#include "../include/raylib.h"
#include "../include/entt.hpp"


#define CHAR_WIDTH 32
#define CHAR_HEIGHT 64

using namespace std;

int main()
{
	// Create the main window	
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	InitWindow(screenWidth, screenHeight, "CS370");
	ToggleFullscreen();


	//init entt registry
	entt::registry registry;
	Texture texture();

	


	//init test entities
	for (size_t i = 0; i < 10; i++)
	{
		//create a new entity
		entt::entity entity = registry.create();
		registry.emplace<Transform>(entity, Vector2{float(i * 50), float(i * 50)}, Vector2{CHAR_WIDTH, CHAR_HEIGHT}, 0.0f);
		registry.emplace<Texture>(entity, "../../../assets/advnt_full.png", CHAR_WIDTH, CHAR_HEIGHT);
	}


	// Box properties
	/*
	Vector2 boxPosition = {400, 300};   // Start in middle
    Vector2 boxSize = {32, 64};         // Width & height
    float speed = 400.0f;               // Pixels per second
	*/

	
	// Main game loop
    SetTargetFPS(60);
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		float dt = GetFrameTime(); // Time since last frame

		update(registry, dt);

				// Update
		//rotation++;

		BeginDrawing();
		ClearBackground(RAYWHITE);
		 DrawRectangleV(boxPosition, boxSize, BLUE); // Draw the box

         DrawText("Move with W A S D", 10, 10, 20, BLACK);
		//DrawTexturePro(ball, sourceRec, destRec, origin, (float)rotation, GREEN);

		EndDrawing();
	}

	// Cleanup
	UnloadTexture(cow);
	//UnloadTexture(background);
	UnloadTMX(stage1);
	CloseWindow();

	return 0;
}