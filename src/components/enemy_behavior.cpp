#include "enemy_behavior.hpp"

void TestUpdateFunc(entt::registry &reg, float dt){
    TraceLog(LOG_TRACE, "Entering TestUpdateFunc");
    TraceLog(LOG_TRACE, "Exiting TestUpdateFunc");
}


Enemy_behavior::Enemy_behavior(UpdateFunction Update){
    this->Update = Update;
}