#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../../include/entt.hpp"
#include "../../include/raylib.h"

struct PlayerCamera{};

void CreateCamera(entt::registry &registry);

void SetCameraPos(Camera2D &camera, Transform newPos);


#endif // CAMERA_HPP