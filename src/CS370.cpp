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

		// Move box based on key input
		if (IsKeyDown(KEY_D)) boxPosition.x += speed * dt;
		if (IsKeyDown(KEY_A)) boxPosition.x -= speed * dt;
		if (IsKeyDown(KEY_W)) boxPosition.y -= speed * dt;
		if (IsKeyDown(KEY_S)) boxPosition.y += speed * dt;

		// Constrain box to stay within screen bounds
		if (boxPosition.x < 0) boxPosition.x = 0;
		if (boxPosition.y < 0) boxPosition.y = 0;
		if (boxPosition.x > screenWidth - boxSize.x) boxPosition.x = screenWidth - boxSize.x;
		if (boxPosition.y > screenHeight - boxSize.y) boxPosition.y = screenHeight - boxSize.y;

		// Update cow texture position to follow the box
		destRec.x = boxPosition.x;
		destRec.y = boxPosition.y;

		BeginDrawing();
		DrawTexturePro(background, 
			{0, 0, (float)background.width, (float)background.height}, 
			{0, 0, (float)screenWidth, (float)screenHeight}, 
			{0, 0}, 0, WHITE);

		 DrawTexturePro(cow, sourceRec, destRec, origin, (float)rotation, WHITE); // Draw cow over the box

         DrawText("Move with W A S D", 10, 10, 20, BLACK);

		EndDrawing();
	}

	// Cleanup
	UnloadTexture(cow);
	//UnloadTexture(background);
	UnloadTMX(stage1);
	CloseWindow();

	return 0;
}