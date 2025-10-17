    #include "player_stats.hpp"
     
    
    PlayerStats::PlayerStats(int maxHealth, float jumpStrength, float gravity, int maxIFrames) {
        this->maxHealth = maxHealth;
        this->health = maxHealth;
        this->jumpStrength = jumpStrength;
        this->gravity = gravity;
        this->maxIFrames = maxIFrames;
        this->iFrames = 0;
    }