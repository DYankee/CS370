#include "animation.hpp"

// Constructor
Animation::Animation() 
    : currentFrame(0), frameTimer(0.0f), isPlaying(false), hasFinished(false) {}

// Add an animation sequence to the component
void Animation::AddSequence(const std::string& name, const AnimationSequence& sequence) {
    sequences[name] = sequence;
    
    // If this is the first sequence, set it as current
    if (sequences.size() == 1) {
        currentSequence = name;
    }
}

// Play a specific animation sequence
void Animation::PlaySequence(const std::string& name) {
    auto it = sequences.find(name);
    if (it != sequences.end()) {
        // Only reset if switching to a different animation
        if (currentSequence != name) {
            currentSequence = name;
            currentFrame = 0;
            frameTimer = 0.0f;
            hasFinished = false;
        }
        isPlaying = true;
    } else {
        TraceLog(LOG_ERROR, "Animation sequence '%s' not found!", name.c_str());
    }
}

// Update the animation
void Animation::Update(float deltaTime) {
    if (!isPlaying || hasFinished) {
        return;
    }

    auto it = sequences.find(currentSequence);
    if (it == sequences.end() || it->second.frames.empty()) {
        return;
    }

    const AnimationSequence& sequence = it->second;
    
    // Update frame timer
    frameTimer += deltaTime;

    // Check if we should advance to the next frame
    if (frameTimer >= sequence.frames[currentFrame].duration) {
        frameTimer = 0.0f;
        currentFrame++;

        // Check if animation has completed
        if (currentFrame >= static_cast<int>(sequence.frames.size())) {
            if (sequence.loop) {
                currentFrame = 0;  // Loop back to start
            } else {
                currentFrame = static_cast<int>(sequence.frames.size()) - 1;  // Stay on last frame
                hasFinished = true;
                isPlaying = false;
            }
        }
    }
}

// Reset the current animation to the beginning
void Animation::Reset() {
    currentFrame = 0;
    frameTimer = 0.0f;
    hasFinished = false;
}

// Pause the animation
void Animation::Pause() {
    isPlaying = false;
}

// Resume the animation
void Animation::Resume() {
    if (!hasFinished) {
        isPlaying = true;
    }
}

// Get the current frame's source rectangle
Rectangle Animation::GetCurrentFrame() const {
    auto it = sequences.find(currentSequence);
    if (it != sequences.end() && !it->second.frames.empty()) {
        int frameIndex = currentFrame < static_cast<int>(it->second.frames.size()) 
                         ? currentFrame 
                         : static_cast<int>(it->second.frames.size()) - 1;
        return it->second.frames[frameIndex].srcRec;
    }
    
    // Return empty rectangle if no valid frame
    return Rectangle{0, 0, 0, 0};
}

// Check if the animation has finished 
bool Animation::IsFinished() const {
    return hasFinished;
}
