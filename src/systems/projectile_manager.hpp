#ifndef PROJECTILE_MANAGER_HPP
#define PROJECTILE_MANAGER_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"


// Function to update all projectiles
void UpdateProjectiles(entt::registry&, float);

bool CheckProjectilePlayerCollision(entt::registry &registry, entt::entity projectile);
bool CheckProjectileMapCollision(entt::registry &registry, entt::entity projectile);
bool CheckProjectileEnemyCollision(entt::registry &registry, entt::entity projectile);

void ApplyProjectileDamage(entt::registry &registry, entt::entity projectile);

void RemoveAllProjectiles(entt::registry &registry);



#endif
