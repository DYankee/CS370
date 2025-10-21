#include "camera.hpp"

void CreateCamera(entt::registry &registry) {
    TraceLog(LOG_TRACE, "Entering Function: CreateCamera");
    TraceLog(LOG_INFO, "Creating Camera Entity");
    
    entt::entity cameraEntity = registry.create();
    registry.emplace<PlayerCamera>(cameraEntity);

    Camera2D camera;
    camera.zoom = 2.0f;
    camera.target = {0.0f, 0.0f};
    camera.offset = {0.0f, 0.0f};
    camera.rotation = 0.0f;
    registry.emplace<Camera2D>(cameraEntity, camera);
}

void SetCameraPos(Camera2D &camera, Transform newPos) {
    TraceLog(LOG_TRACE, "Entering Function: SetCameraPos");
    TraceLog(LOG_INFO, "Moving camera from: %f,%f to: %f,%f",
        camera.target.x,
        camera.target.y,
        newPos.translation.x / 2,
        newPos.translation.y / 2
    );

    // Update camera pos
    camera.target.x = newPos.translation.x / 2;
    camera.target.y = newPos.translation.y / 2;
}