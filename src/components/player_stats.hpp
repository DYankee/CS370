#ifndef PLAYER_STATS_HPP
#define PLAYER_STATS_HPP


struct PlayerStats {
    int health;         //plater current health
    int maxHealth;      //player max health
    int iFrames;        // remaining i frame
    int maxIFrames;     // max i frame duration in frames
    float jumpStrength; //jump strength
    float gravity;      //gravity affecting player


    PlayerStats(int maxHealth, float jumpStrength, float gravity, int maxIFrames);
};

#endif