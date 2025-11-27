#ifndef DIALOGUE_HPP
#define DIALOGUE_HPP

#include <string>
#include <vector>

struct Dialogue {
    std::vector<std::string> lines;
    bool isActive;
    float displayTimer;
    float displayDuration;
    
    Dialogue(const std::vector<std::string>& dialogueLines, float duration = 3.0f) 
        : lines(dialogueLines), isActive(false), displayTimer(0.0f), displayDuration(duration) {}
    
    void Show() {
        isActive = true;
        displayTimer = displayDuration;
    }
    
    void Update(float dt) {
        if (isActive) {
            displayTimer -= dt;
            if (displayTimer <= 0.0f) {
                isActive = false;
            }
        }
    }
};

#endif
