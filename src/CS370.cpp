// CS370.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "../include/raylib.h"
#include "../include/entt.hpp"


#define CHAR_WIDTH 32
#define CHAR_HEIGHT 64

using namespace std;

/*
struct My_Transform {
	Vector2 position;
	Vector2 size;
	float rotation;
};
struct My_Texture {
	Texture2D texture;
   	Rectangle sourceRec;

	My_Texture(std::string filePath, int frameW, int frameH){
		// Default constructor
		texture = LoadTexture(filePath.c_str());
		sourceRec = { 0.0f, 0.0f, (float)frameW, (float)frameH};
	}
};
*/

void update(entt::registry& registry, float dt) {

	// Update all entities with Transform and Texture components
	registry.view<Transform>().each([dt](auto& transform) {
		// Example update logic: Move the entity to the right
		transform += 1.0f * dt; // Move right by 1 unit per update
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
	registry.view<Transform, Texture>().each([](auto& transform, auto& texture) {
		// Draw the texture at the entity's position
		DrawTexturePro(texture.texture,
			texture.sourceRec,
			Rectangle{
				transform.position.x, transform.position.y,
				transform.size.x, transform.size.y
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

	 // Box properties
    Vector2 boxPosition = {400, 300};   // Start in middle
    Vector2 boxSize = {50, 50};         // Width & height
    float speed = 400.0f;               // Pixels per second


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

		// Update
		//rotation++;

		BeginDrawing();
		draw(registry);
		ClearBackground(RAYWHITE);

		
		 DrawRectangleV(boxPosition, boxSize, BLUE); // Draw the box

         DrawText("Move with W A S D", 10, 10, 20, BLACK);
		//DrawTexturePro(ball, sourceRec, destRec, origin, (float)rotation, GREEN);

		EndDrawing();
	}
	return 0;
}
