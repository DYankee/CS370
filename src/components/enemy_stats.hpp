#ifndef ENEMY_STATS_HPP
#define ENEMY_STATS_HPP

enum Direction {LEFT, RIGHT};

Direction ChangeDirection(Direction);

struct EnemyStats {
    int enemyHealth;            //enemy's current health
    int enemyMaxHealth;         //enemy's maxiumum health
    float enemySpeed;           //enemy's movement speed
    float dmg;                  //enemy's dmg to the player
    Direction CurrentDirection; //enemy's Current direction
    bool followsPlayer;         //determines whether enemy follows the player or not

    EnemyStats(int enemyHealth, int enemyMaxHealth, float enemySpeed, float dmg, Direction direction, bool followsPlayer);
};

#endif