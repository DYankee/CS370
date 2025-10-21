#include "camera_controller.hpp"

void CameraUpdate(entt::registry &registry, float dt) {
    TraceLog(LOG_TRACE, "Entering Function: CameraUpdate");
    TraceLog(LOG_INFO, "Updating Camera");

    // Update camera to follow the player
    registry.view<PlayerCamera, Camera2D>().each([&registry](Camera2D &camera) {
        registry.view<Transform, Player>().each([&camera](Transform &transform) {
            SetCameraPos(camera, transform);
        });
    });
}