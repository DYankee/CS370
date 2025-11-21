#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"
#include "../components/components.hpp"
#include "../components/projectile_stats.hpp"


struct Projectile{};

//void CreateProjectile(entt::registry&, Transform, Vector3);
void CreateProjectile(entt:: registry&, Transform, Vector3, ProjectileStats);


#endif
