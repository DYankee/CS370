// CS370.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "../include/raylib.h"
#include "../include/entt.hpp"


#define CHAR_WIDTH 32.0f
#define CHAR_HEIGHT 64.0f

using namespace std;

struct My_Texture {
	Texture2D texture;
	float width;
	float height;
   	Rectangle sourceRec;

	My_Texture(std::string filePath, float frameW, float frameH){
		// Default constructor
		texture = LoadTexture(filePath.c_str());
		width = frameW;
		height = frameH;
		sourceRec = { 0.0f, 0.0f, frameW, frameH};
	}
};

struct Transform2D {
	Vector2 translation;    // Translation
	Vector2 scale;          // Scale
	float rotation;			// Rotation

	Transform2D(Vector2 pos, Vector2 scl, float rot) {
		translation = pos;
		scale = scl;
		rotation = rot;
	}
};

struct Stats{
	float moveSpeed = 0;

	Stats(float speed) {
		moveSpeed = speed;
	}
};

void update(entt::registry& registry, float dt) {

	// Update all entities with Transform and Texture components
	registry.view<Transform2D, Stats>().each([dt](auto& transform, auto& stats) {
		// Example update logic: Move the entity to the right
		transform.translation.x += stats.moveSpeed * dt; // Move right by 1 unit per update
	});

	// Move box based on key input
	/*
	if (IsKeyDown(KEY_D)) boxPosition.x += speed * dt;
	if (IsKeyDown(KEY_A)) boxPosition.x -= speed * dt;
	if (IsKeyDown(KEY_W)) boxPosition.y -= speed * dt;
	if (IsKeyDown(KEY_S)) boxPosition.y += speed * dt;
	
	// Constrain box to stay within screen bounds
	if (boxPosition.x < 0) boxPosition.x = 0;
	if (boxPosition.y < 0) boxPosition.y = 0;
	if (boxPosition.x > screenWidth - boxSize.x) boxPosition.x = screenWidth - boxSize.x;
	if (boxPosition.y > screenHeight - boxSize.y) boxPosition.y = screenHeight - boxSize.y;
	*/
}

void draw(entt::registry& registry) {
	// Draw all entities with Transform and Texture components
	registry.view<Transform2D, My_Texture>().each([](auto& transform, auto& texture) {
		// Draw the texture at the entity's position
		DrawTexturePro(texture.texture,
			texture.sourceRec,
			Rectangle{
				transform.translation.x, transform.translation.y,
				texture.width, texture.height
			},
			{0.0f, 0.0f},
			transform.rotation,
			BLACK);
	});
}



int main()
{
	// Create the main window	
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	InitWindow(screenWidth, screenHeight, "CS370");
	ToggleFullscreen();
	
	//init variables
	const float gravity = 1000.0f;

	 // Box properties
    Vector2 boxPosition = {400.0f, 300.0f};   // Start in middle
    Vector2 boxSize = {50, 50};         // Width & height
	Vector2 boxVol = {0.0f, 0.0f};      // Box Volocity
    float speed = 400.0f;               // Pixels per second
	float jumpStrength = -400.0f;       // Initial upward velocity

	// Load cow texture
	Texture2D cow = LoadTexture("../assets/cow.png");

	// Load background texture
	Texture2D background = LoadTexture("../assets/bg.png");

    int frameWidth = cow.width;
    int frameHeight = cow.height;

    // Source rectangle (part of the texture to use for drawing)
    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight};

    // Destination rectangle (screen rectangle where drawing part of texture)
    Rectangle destRec = { boxPosition.x, boxPosition.y, (float)boxSize.x, (float)boxSize.y };

    // Origin of the texture (rotation/scale point), it's relative to destination rectangle size
    Vector2 origin = { 0, 0 };

    int rotation = 0;

	// Main game loop
    SetTargetFPS(60);
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{

<<<<<<< HEAD
=======
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

>>>>>>> 3e558d3 (added test ui elements to draw over the background and cube)
		// Update
		rotation++;

		// Draw
		BeginDrawing();
		DrawTexturePro(background, 
			{0, 0, (float)background.width, (float)background.height}, 
			{0, 0, (float)screenWidth, (float)screenHeight}, 
			{0, 0}, 0, WHITE);

		 DrawTexturePro(cow, sourceRec, destRec, origin, (float)rotation, WHITE); // Draw cow over the box

         DrawText("Move with W A S D", 10, 10, 20, BLACK);
		//DrawTexturePro(ball, sourceRec, destRec, origin, (float)rotation, GREEN);
>>>>>>> 3e558d3 (added test ui elements to draw over the background and cube)

		EndDrawing();
	}

	// Cleanup
	UnloadTexture(cow);
	UnloadTexture(background);
	CloseWindow();

	return 0;
}
