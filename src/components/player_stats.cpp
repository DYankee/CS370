    #include "player_stats.hpp"
     
    
    PlayerStats::PlayerStats(int maxHealth, float maxIFrames, float speed, float jumpStrength, float gravity) {
        this->maxHealth = maxHealth;
        this->health = maxHealth;
        this->maxIFrames = maxIFrames;
        this->iFrames = 0;
        this->speed = speed;
        this->jumpStrength = jumpStrength;
        this->gravity = gravity;
    }