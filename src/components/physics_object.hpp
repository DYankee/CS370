#ifndef PHYSICS_OBJECT_HPP
#define PHYSICS_OBJECT_HPP

#include "components.hpp"

struct PhysicsObject {
    float mass;
    Vector2 velocity;

    PhysicsObject(float mass, Vector2 velocity);
};

#endif