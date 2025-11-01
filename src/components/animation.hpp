#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "../../include/raylib.h"
#include <map>
#include <string>
#include <vector>

struct AnimationFrame {
    Rectangle srcRec;       // Source rectangle in the sprite sheet
    float duration;         // Duration of this frame in seconds
};

struct AnimationSequence {
    std::vector<AnimationFrame> frames;
    bool loop;             
    AnimationSequence() : loop(true) {}
    AnimationSequence(std::vector<AnimationFrame> frames, bool loop = true) 
        : frames(frames), loop(loop) {}
};

struct Animation {
    std::map<std::string, AnimationSequence> sequences;  // Named animation sequences
    std::string currentSequence;                         // Current animation name
    int currentFrame;                                    // Current frame index
    float frameTimer;                                    // Timer for current frame
    bool isPlaying;                                      // Is animation playing
    bool hasFinished;                                    // Has non-looping animation finished

    // Constructor
    Animation();
    
    // Methods
    void AddSequence(const std::string& name, const AnimationSequence& sequence);
    void PlaySequence(const std::string& name);
    void Update(float deltaTime);
    void Reset();
    void Pause();
    void Resume();
    Rectangle GetCurrentFrame() const;
    bool IsFinished() const;
};

#endif // ANIMATION_HPP