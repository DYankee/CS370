#include "enemy_stats.hpp"

EnemyStats::EnemyStats(int enemyHealth, int enemyMaxHealth, float enemySpeed, float dmg, bool followsPlayer) {
    this->enemyHealth = enemyMaxHealth;
    this->enemyMaxHealth = enemyMaxHealth;
    this->enemySpeed = enemySpeed;
    this->dmg = dmg;
    this->followsPlayer = followsPlayer;
}