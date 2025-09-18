// CS370.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "../include/raylib.h"
#include "../include/entt.hpp"


#define CHAR_WIDTH 32
#define CHAR_HEIGHT 64

using namespace std;

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

void update(entt::registry& registry, float dt) {

	// Update all entities with Transform and Texture components
	registry.view<My_Transform>().each([dt](auto& transform) {
		// Example update logic: Move the entity to the right
		transform.position.x += 1.0f * dt; // Move right by 1 unit per update
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
	registry.view<My_Transform, My_Texture>().each([](auto& transform, auto& texture) {
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


	//init entt registry
	entt::registry registry;



	//init test entities
	for (size_t i = 0; i < 10; i++)
	{
		entt::entity entity = registry.create();
		registry.emplace<My_Transform>(entity, Vector2{float(i * 50), float(i * 50)}, Vector2{CHAR_WIDTH, CHAR_HEIGHT}, 0.0f);
		registry.emplace<My_Texture>(entity, "../../../assets/advnt_full.png", CHAR_WIDTH, CHAR_HEIGHT);
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
		draw(registry);
		ClearBackground(RAYWHITE);

		
		//DrawRectangleV(boxPosition, boxSize, BLUE); // Draw the box
        //DrawText("Move with W A S D", 10, 10, 20, BLACK);
		//DrawTexturePro(ball, sourceRec, destRec, origin, (float)rotation, GREEN);

		EndDrawing();
	}
	return 0;
}
