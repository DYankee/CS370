#include "player.hpp"
#include "../components/components.hpp"



// Player struct constructor
Player::Player(){};

// Function to create the player entity
void createPlayer(entt::registry &registry, Camera2D camera) {

    // Add Player entity to the registry
    entt::entity playerEnt = registry.create();

    // Add Player component to the entity
    Player playerComponent;
    registry.emplace<Player>(playerEnt, playerComponent);


    // Load player sprites
    SpriteData cowSprite = SpriteData(loadTextures({
            {"cowR", "assets/sprites/cowR.png"},
            {"cowL", "assets/sprites/cowL.png"}}),
        WHITE
    );
    cowSprite.setTexture("cowR");
    // Add SpriteData component to the entity
    registry.emplace<SpriteData>(playerEnt, cowSprite);

    // Add Transform component to the entity
    Transform playerTransform = Transform{ {400.0f, 300.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {CHAR_WIDTH, CHAR_HEIGHT} };
    registry.emplace<Transform>(playerEnt, playerTransform);

    // Add Camera component to the entity
    registry.emplace<Camera>(playerEnt, camera);

    // Add PhysicsObject component to the entity
    PhysicsObject physics = PhysicsObject(1.0f, {0.0f, 0.0f});
    registry.emplace<PhysicsObject>(playerEnt, physics);

    // Add the rest of the components needed for the player here
};

// Player movement system
void playerMovementSystem(entt::registry &registry, float dt, float gravity) {

    // Get the Transform and PhysicsObject from the Player Component
    registry.view<Transform, PhysicsObject, SpriteData, Player>().each([dt, gravity, &registry](Transform transform, PhysicsObject physics, SpriteData sprite) {

        transform.translation.y += gravity * dt;
        // Move box based on key input
        if (IsKeyDown(KEY_D)) {
            physics.velocity.x = SPEED;    // Move right
            sprite.setTexture("cowR");
        } else if (IsKeyDown(KEY_A)) {
            physics.velocity.x = -SPEED;   // Move left
            sprite.setTexture("cowL");
        } else {
            physics.velocity.x = 0;        // No horizontal movement
        }

        // Only allow jump if player is on the ground
        if (IsKeyPressed(KEY_SPACE)) {
            registry.view<TmxMap>().each([&transform, &physics, &sprite](TmxMap* map){{
                Rectangle testRec = { transform.translation.x, transform.translation.y + 1, transform.scale.x, transform.scale.y };
                TmxObject collidedObj;
                bool onGround = CheckCollisionTMXTileLayersRec(
                    map, map->layers, map->layersLength, testRec, &collidedObj
                );
                if (onGround) {
                    physics.velocity.y = JUMP_STRENGTH;
                }
            }});
        }
        // Calculate new position
        transform.translation.x += physics.velocity.x * dt;
        transform.translation.y += physics.velocity.y * dt;
    });
}
    // Constants