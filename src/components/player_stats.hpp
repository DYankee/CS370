#ifndef PLAYER_STATS_HPP
#define PLAYER_STATS_HPP

#include "../../include/raylib.h"

struct PlayerStats {
    int health;         //plater current health
    int maxHealth;      //player max health
    float iFrames;      // remaining i frame
    float maxIFrames;   // max i frame duration in frames
    float speed;        //player movement speed
    float jumpStrength; //jump strength
    float gravity;      //gravity affecting player
    Sound jumpSound;    //jump sound effect


    PlayerStats(int maxHealth, float maxIFrames, float speed, float jumpStrength, float gravity, Sound jumpSound);
};

#endif