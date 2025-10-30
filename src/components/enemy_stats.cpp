#include "enemy_stats.hpp"

EnemyStats::EnemyStats(int enemyHealth, int enemyMaxHealth, float enemySpeed, bool followsPlayer) {
    this->enemyHealth = enemyMaxHealth;
    this->enemyMaxHealth = enemyMaxHealth;
    this->enemySpeed = enemySpeed;
    this->followsPlayer = followsPlayer;
}