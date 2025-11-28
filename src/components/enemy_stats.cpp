#include "enemy_stats.hpp"


Direction ChangeDirection(Direction d){
    Direction direction;
    if(d == LEFT){
        direction = RIGHT;
    }
    else if (d == RIGHT){
        direction = LEFT;
    }
    return direction;
}

EnemyStats::EnemyStats(EnemyType type, int enemyMaxHealth, float enemySpeed, float dmg, float attackCooldown, Direction direction, bool aggro) {
    this->type = type;
    this->enemyHealth = enemyMaxHealth;
    this->enemyMaxHealth = enemyMaxHealth;
    this->enemySpeed = enemySpeed;
    this->dmg = dmg;
    this->attackCooldown = attackCooldown;
    this->attackCooldownTimer = 0;
    this->CurrentDirection = direction;
    this->aggro = aggro;
    this->spawnPauseTimer = 0.5f; // 0.5 second spawn pause
}