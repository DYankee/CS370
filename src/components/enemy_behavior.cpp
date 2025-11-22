#include "enemy_behavior.hpp"
#include "sprite_data.hpp"

void TestUpdateFunc(entt::registry &registry, float dt, entt::entity enemy){
    TraceLog(LOG_TRACE, "Entering TestUpdateFunc");

    // Get components from enemy entity
    auto& pos = registry.get<Transform>(enemy);
    auto& physics = registry.get<PhysicsObject>(enemy);
    auto& stats = registry.get<EnemyStats>(enemy);

    pos.translation.x += stats.enemySpeed * dt;
    TraceLog(LOG_TRACE, "Exiting TestUpdateFunc");
}

void BasicEnemyUpdate(entt::registry & registry, float dt, entt::entity enemy){
    TraceLog(LOG_TRACE, "Entering Function BasicEnemyUpdate");
    TraceLog(LOG_INFO, "Updating entity: %d", enemy);
    float maxDistance = 50;
    
    // Get player position
    auto players = registry.view<Player>();
    entt::entity player = players.front();
    auto& playerPos = registry.get<Transform>(player);

    // Get components from enemy entity    auto& pos = registry.get<Transform>(enemy);
    auto& pos = registry.get<Transform>(enemy);
    auto& physics = registry.get<PhysicsObject>(enemy);
    auto& stats = registry.get<EnemyStats>(enemy);
    auto& spawn = registry.get<Vector2>(enemy);
    auto& sprite = registry.get<SpriteData>(enemy);

    // Apply gravity
    physics.velocity.y += GRAVITY * dt;

    // Check if we are following the player
    if(stats.aggro){

        // Move towards player
        if (pos.translation.x < playerPos.translation.x){
            stats.CurrentDirection = RIGHT;
        } else {
            stats.CurrentDirection = LEFT;
        }

        // Check if we should stop following the player
        float distanceFromPlayer = abs(pos.translation.x - playerPos.translation.x);
        if (distanceFromPlayer > 200){
            stats.aggro = false;
        }
    } else {

        // Check distance from spawn point
        int distanceFromSpawn = abs(pos.translation.x - spawn.x);
        
        // set direction based on distance from spawn 
        if(distanceFromSpawn > maxDistance){
            if(pos.translation.x > spawn.x){
                stats.CurrentDirection = LEFT;
            }
            else{
                stats.CurrentDirection = RIGHT;
                sprite.SetTexture("FarmerR");
            }
        }


        // Check if we should start following the player
        float distanceFromPlayer = abs(pos.translation.x - playerPos.translation.x);
        if (distanceFromPlayer < 100){
            stats.aggro = true;
        }
    }
    // Move based on current direction
    if(stats.CurrentDirection == LEFT){
        physics.velocity.x = stats.enemySpeed * -1;
        sprite.SetTexture("FarmerL");
    }
    else if(stats.CurrentDirection == RIGHT){
        physics.velocity.x = stats.enemySpeed * 1;
        sprite.SetTexture("FarmerR");
    }
    MoveEntity(registry, dt, enemy);
}

void RangedEnemyUpdate(entt::registry & registry, float dt, entt::entity enemy){
    TraceLog(LOG_TRACE, "Entering Function RangedEnemyUpdate:");
    TraceLog(LOG_INFO, "Updating entity: %d", enemy);
    
    // Get player position
    auto players = registry.view<Player>();
    entt::entity player = players.front();
    auto& playerPos = registry.get<Transform>(player);

    // Get components from enemy entity    auto& pos = registry.get<Transform>(enemy);
    auto& pos = registry.get<Transform>(enemy);
    auto& physics = registry.get<PhysicsObject>(enemy);
    auto& stats = registry.get<EnemyStats>(enemy);
    auto& spawn = registry.get<Vector2>(enemy);
    auto& sprite = registry.get<SpriteData>(enemy);

    // Check if we are following the player
    TraceLog(LOG_INFO, "RangedEnemyUpdate: Checking if enemy(%d) should attack", enemy);
    TraceLog(LOG_INFO, "RangedEnemyUpdate: enemy(%d) shouldAttack(%s), cd(%f)",
        enemy, stats.aggro ? "True" : "False",
        stats.attackCooldownTimer
    );
    if(stats.aggro && stats.attackCooldownTimer < 0){
        TraceLog(LOG_INFO, "RangedEnemyUpdate: enemy(%d) should attack", enemy);
        TraceLog(LOG_INFO, "RangedEnemyUpdate: creating projectile at(%f,%f), with a target of(%f,%f)",
            pos.translation.x, pos.translation.y,
            playerPos.translation.x, playerPos.translation.y
        );
        CreateProjectile(registry, pos, playerPos.translation, ProjectileStats{100,1});
        stats.attackCooldownTimer = stats.attackCooldown;
    } 
    else {
        TraceLog(LOG_INFO, "RangedEnemyUpdate: reducing enemy(%d) attackCooldown from(%f) to(%f)", 
            enemy,
            stats.attackCooldownTimer,
            stats.attackCooldownTimer -= dt
        );
        stats.attackCooldownTimer -= dt;
    }

    // Check for aggro/de-aggro
    float dx = pos.translation.x - playerPos.translation.x;
    float dy = pos.translation.y - playerPos.translation.y;
    float distanceSquared = (dx * dx) + (dy * dy);
    float PlayerDistance = std::sqrt(distanceSquared);
    if(PlayerDistance < 500){
        stats.aggro = true;
    }
    else {
        stats.aggro = false;
    }
    
    
    // Apply gravity
    physics.velocity.y += GRAVITY * dt;
    
    MoveEntity(registry, dt, enemy);
}


Enemy_behavior::Enemy_behavior(UpdateFunction Update){
    this->Update = Update;
}