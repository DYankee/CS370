#ifndef ENEMY_STATS_HPP
#define ENEMY_STATS_HPP

enum Direction {LEFT, RIGHT};

Direction ChangeDirection(Direction);

struct EnemyStats {
    int enemyHealth;            //enemy's current health
    int enemyMaxHealth;         //enemy's maximum health
    float enemySpeed;           //enemy's movement speed
    float dmg;                  //enemy's dmg to the player
    float attackCooldown;       //Time between enemy attacks
    float attackCooldownTimer;  //Current attack cooldown
    Direction CurrentDirection; //enemy's Current direction
    bool aggro;         //determines whether enemy follows the player or not

    EnemyStats(int enemyMaxHealth, float enemySpeed, float dmg, float attackCooldown, Direction direction, bool aggro);
};

#endif