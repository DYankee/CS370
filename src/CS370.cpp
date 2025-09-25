// CS370.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "../include/raylib.h"

#define RAYTMX_IMPLEMENTATION
#include "../include/raytmx.h"

using namespace std;

int main()
{
	// Create entt registry
	entt::registry registry = entt::registry();
	map<string, entt::entity> entityMap;
	
	// Create the main window	
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	InitWindow(screenWidth, screenHeight, "CS370");
	ToggleFullscreen();

    // Load TMX map
    TmxMap* stage1 = LoadTMX("../assets/tiled/stage1.tmx");
    if (!stage1) {
        cout << "Failed to load stage1.tmx" << endl;
        CloseWindow();
        return -1;
    }
	
	//init variables
	const float gravity = 1000.0f;

	 // Box properties
    Vector2 boxPosition = {400.0f, 300.0f};   // Start in middle
    Vector2 boxSize = {50, 50};         // Width & height
	Vector2 boxVol = {0.0f, 0.0f};      // Box Volocity
	 // Box properties
    Vector2 boxPosition = {400.0f, 300.0f};   // Start in middle
    Vector2 boxSize = {50, 50};         // Width & height
	Vector2 boxVol = {0.0f, 0.0f};      // Box Volocity
    float speed = 400.0f;               // Pixels per second
	float jumpStrength = -400.0f;       // Initial upward velocity
	float jumpStrength = -400.0f;       // Initial upward velocity

	// Load cow texture
	Texture2D cow = LoadTexture("../assets/sprites/cow.png");

	int frameWidth = cow.width;
    int frameHeight = cow.height;

	// Load background texture
	//Texture2D background = LoadTexture("../assets/sprites/bg.png");

    // Source rectangle (part of the texture to use for drawing)
    //Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight};

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

		boxVol.y += gravity * dt; // Update volocity based on gravity

		// Move box based on key input
		if (IsKeyPressed(KEY_SPACE)) // if player hits space jump 
		{
   			boxVol.y = jumpStrength; // player jumps using jump strength
		}

		if (IsKeyDown(KEY_D)) boxPosition.x += speed * dt; // move left
		if (IsKeyDown(KEY_A)) boxPosition.x -= speed * dt; // move right

		boxPosition.y += boxVol.y * dt; // update player position based on volocity

		// Constrain box to stay within screen bounds
		if (boxPosition.x < 0) boxPosition.x = 0;
		if (boxPosition.y < 0) boxPosition.y = 0;
		if (boxPosition.x > screenWidth - boxSize.x) boxPosition.x = screenWidth - boxSize.x;
		if (boxPosition.y > screenHeight - boxSize.y) boxPosition.y = screenHeight - boxSize.y;

		float dt = GetFrameTime(); // Time since last frame

		boxVol.y += gravity * dt; // Update volocity based on gravity

		// Move box based on key input
		if (IsKeyPressed(KEY_SPACE)) // if player hits space jump 
		{
   			boxVol.y = jumpStrength; // player jumps using jump strength
		}

		if (IsKeyDown(KEY_D)) boxPosition.x += speed * dt; // move left
		if (IsKeyDown(KEY_A)) boxPosition.x -= speed * dt; // move right

		boxPosition.y += boxVol.y * dt; // update player position based on volocity

		// Constrain box to stay within screen bounds
		if (boxPosition.x < 0) boxPosition.x = 0;
		if (boxPosition.y < 0) boxPosition.y = 0;
		if (boxPosition.x > screenWidth - boxSize.x) boxPosition.x = screenWidth - boxSize.x;
		if (boxPosition.y > screenHeight - boxSize.y) boxPosition.y = screenHeight - boxSize.y;

		// Update
		update(registry, dt);

		float dt = GetFrameTime(); // Time since last frame

		boxVol.y += gravity * dt; // Update volocity based on gravity

		// Move box based on key input
		if (IsKeyPressed(KEY_SPACE)) // if player hits space jump 
		{
   			boxVol.y = jumpStrength; // player jumps using jump strength
		}

		if (IsKeyDown(KEY_D)) boxPosition.x += speed * dt; // move left
		if (IsKeyDown(KEY_A)) boxPosition.x -= speed * dt; // move right

		boxPosition.y += boxVol.y * dt; // update player position based on volocity

		// Constrain box to stay within screen bounds
		if (boxPosition.x < 0) boxPosition.x = 0;
		if (boxPosition.y < 0) boxPosition.y = 0;
		if (boxPosition.x > screenWidth - boxSize.x) boxPosition.x = screenWidth - boxSize.x;
		if (boxPosition.y > screenHeight - boxSize.y) boxPosition.y = screenHeight - boxSize.y;

		// Update cow texture position to follow the box
		destRec.x = boxPosition.x;
		destRec.y = boxPosition.y;

		BeginDrawing();
		ClearBackground(RAYWHITE);

		// Draw background texture scaled to screen size
		
		/*DrawTexturePro(background, 
			{0, 0, (float)background.width, (float)background.height}, 
			{0, 0, (float)screenWidth, (float)screenHeight}, 
			{0, 0}, 0, WHITE);*/

		// Draw the map
        DrawTMX(stage1, NULL, 0, 0, WHITE);

		 //DrawRectangleV(boxPosition, boxSize, BLUE); // Draw the blue box

		 DrawTexturePro(cow, sourceRec, destRec, origin, (float)rotation, WHITE); // Draw cow over the box
>>>>>>> a2044f2 (commented out draw blue box and clear background lines)

         DrawText("Move with W A S D", 10, 10, 20, BLACK);

		EndDrawing();
	}

	// Cleanup
	UnloadTexture(cow);
	UnloadTexture(background);
	UnloadTMX(stage1);
	CloseWindow();

	return 0;
}