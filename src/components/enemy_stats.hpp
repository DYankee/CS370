#ifndef ENEMY_STATS_HPP
#define ENEMY_STATS_HPP

struct EnemyStats {
    int enemyHealth;    //enemy's current health
    int enemyMaxHealth; //enemy's maxiumum health
    float enemySpeed;   //enemy's movement speed
    float dmg;          //enemy's dmg to the player
    bool followsPlayer; //determines whether enemy follows the player or not

    EnemyStats(int enemyHealth, int enemyMaxHealth, float enemySpeed, float dmg, bool followsPlayer);
};

#endif