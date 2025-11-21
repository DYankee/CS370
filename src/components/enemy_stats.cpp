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

EnemyStats::EnemyStats(int enemyMaxHealth, float enemySpeed, float dmg, float attackCooldown, Direction direction, bool followsPlayer) {
    this->enemyHealth = enemyMaxHealth;
    this->enemyMaxHealth = enemyMaxHealth;
    this->enemySpeed = enemySpeed;
    this->dmg = dmg;
    this->attackCooldown = attackCooldown;
    this->attackCooldownTimer = 0;
    this->CurrentDirection = direction;
    this->followsPlayer = followsPlayer;
}