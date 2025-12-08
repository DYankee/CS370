#ifndef PLAYER_STATS_HPP
#define PLAYER_STATS_HPP

#include "../../include/raylib.h"

struct PlayerStats {
    int health;         //player current health
    int maxHealth;      //player max health
    float iFrames;      // remaining i frame
    float maxIFrames;   // max i frame duration in frames
    float speed;        //player movement speed
    float jumpStrength; //jump strength
    float gravity;      //gravity affecting player
    Sound jumpSound;    //jump sound effect
    bool isAttacking = false; //is player attacking
    float spawnPauseTimer;      //Timer for spawn pause (0.5 second)
    bool hasRanged = false; // Check if player has ranged attack

    PlayerStats(int maxHealth, float maxIFrames, float speed, float jumpStrength, float gravity, Sound jumpSound, bool isAttacking, bool hasRanged);
};

struct PlayerUpgrades {
    bool testUpgrade;
    bool doubleJumpUpgrade;

    PlayerUpgrades(bool testUpgrade, bool doubleJumpUpgrade);
};

#endif