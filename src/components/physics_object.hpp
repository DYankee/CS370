#ifndef PHYSICS_OBJECT_HPP
#define PHYSICS_OBJECT_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"

struct PhysicsObject {
    float mass;
    Vector2 velocity;

    PhysicsObject(float mass, Vector2 velocity);
};

#endif