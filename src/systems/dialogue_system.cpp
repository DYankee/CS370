#include "dialogue_system.hpp"

void UpdateDialogue(entt::registry &registry, float dt) {
    TraceLog(LOG_TRACE, "Entering Function: UpdateDialogue");
    
    // Update all active dialogues
    auto view = registry.view<Dialogue>();
    for (auto entity : view) {
        Dialogue& dialogue = registry.get<Dialogue>(entity);
        dialogue.Update(dt);
    }
}

void DrawDialogue(entt::registry &registry) {
    TraceLog(LOG_TRACE, "Entering Function: DrawDialogue");
    
    // Draw active dialogues
    auto view = registry.view<Dialogue, Transform>();
    for (auto entity : view) {
        Dialogue& dialogue = registry.get<Dialogue>(entity);
        Transform& transform = registry.get<Transform>(entity);
        
        if (dialogue.isActive && !dialogue.lines.empty()) {
            // Calculate total text height
            int fontSize = 20;
            int lineSpacing = 5;
            int padding = 10;
            int totalTextHeight = (fontSize + lineSpacing) * dialogue.lines.size() - lineSpacing;
            
            // Calculate max text width
            int maxWidth = 0;
            for (const auto& line : dialogue.lines) {
                int width = MeasureText(line.c_str(), fontSize);
                if (width > maxWidth) maxWidth = width;
            }
            
            // Position dialogue box above the NPC
            float boxX = transform.translation.x - maxWidth / 2.0f;
            float boxY = transform.translation.y - totalTextHeight - padding * 2 - 10;
            float boxWidth = maxWidth + padding * 2;
            float boxHeight = totalTextHeight + padding * 2;
            
            // Draw background box
            DrawRectangle(boxX, boxY, boxWidth, boxHeight, Fade(BLACK, 0.8f));
            DrawRectangleLines(boxX, boxY, boxWidth, boxHeight, WHITE);
            
            // Draw text lines
            float textY = boxY + padding;
            for (const auto& line : dialogue.lines) {
                float textX = boxX + padding;
                DrawText(line.c_str(), textX, textY, fontSize, WHITE);
                textY += fontSize + lineSpacing;
            }
        }
    }
}
