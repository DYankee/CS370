#include "../systems/player_enemy_collision.hpp"
#include "../components/player_stats.hpp"
#include "../components/enemy_stats.hpp"
#include "../components/physics_object.hpp"

void PlayerEnemyCollisionSystem(entt::registry &registry, float dt) {
    registry.view<PlayerStats, Transform, PhysicsObject>().each(
        [&registry, dt](auto playerEntity, PlayerStats& playerStats, Transform& playerTransform, PhysicsObject& playerPhysics) {
            if (playerStats.iFrames > 0) {
                playerStats.iFrames -= dt;
                return;
            }

            bool stompedEnemy = false;

            registry.view<EnemyStats, Transform, PhysicsObject>().each(
                [&](auto enemyEntity, EnemyStats& enemyStats, Transform& enemyTransform, PhysicsObject& enemyPhysics) {
                    bool collisionX = playerTransform.translation.x < enemyTransform.scale.x + enemyTransform.translation.x &&
                         playerTransform.translation.x + playerTransform.scale.x > enemyTransform.translation.x;

                    bool collisionY = playerTransform.translation.y < enemyTransform.scale.y + enemyTransform.translation.y &&
                         playerTransform.translation.y + playerTransform.scale.y > enemyTransform.translation.y;

                    if (collisionX && collisionY) {
                        float playerBottom = playerTransform.translation.y + playerTransform.scale.y;
                        float enemyTop = enemyTransform.translation.y;
                        bool stomping = playerPhysics.velocity.y > 0 &&
                                        (playerBottom - playerPhysics.velocity.y * dt) <= enemyTop + 5;

                        if (stomping) {
                            registry.destroy(enemyEntity);
                            playerPhysics.velocity.y = -400.0f; // bounce
                            stompedEnemy = true; 
                            return;
                        }

                        if (!stompedEnemy) {
                            playerStats.health -= static_cast<int>(enemyStats.dmg);
                            playerStats.iFrames = playerStats.maxIFrames;

                            const float knockbackX = 300.0f;
                            const float knockbackY = -600.0f;

                            if (playerTransform.translation.x < enemyTransform.translation.x) {
                                playerPhysics.velocity.x = -knockbackX;
                            } else {
                                playerPhysics.velocity.x = knockbackX;
                            }

                            playerPhysics.velocity.y = knockbackY;
                        }
                    }
                }
            );
        }
    );
}
