#include "enemy_behavior.hpp"

void TestUpdateFunc(float dt, EnemyStats &stats, Transform &pos){
    TraceLog(LOG_TRACE, "Entering TestUpdateFunc");
    pos.translation.x += stats.enemySpeed * dt;
    TraceLog(LOG_TRACE, "Exiting TestUpdateFunc");
}


Enemy_behavior::Enemy_behavior(UpdateFunction Update){
    this->Update = Update;
}