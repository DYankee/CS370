# Architectural Spike Plan Document

### Aim to accomplish by the end of current spike:
For our first spike we want the player to be able to load into and move around a simple level. They will also be able to go through a door to move to a new level. Most of our work during this spike will be focused on setting up a framework for the game. This will include starting the game, loading levels, basic physics/collision and basic player movement.

### Features and Responsibility:
- Player movement: Nick
- Level loading: Alaina
- Physics system: Nick
- Platform hitbox: Alaina
- Player hitbox: Alaina
- Git repository setup: Zack
- Build system: Zack
- Basic Tests: Zack
- Incorporating placeholder UI elements: Kent

### Architectural decisions of required systems and how they interact:
- Camera will show the entire level
- Player will be able to move between levels using a door
- Player will be able to move around the level with proper collision

### Schedule of now and between presentation day (10/10/25):
- Week 1 (9/14 - 9/20): Github repo setup, showing basic player object on screen, showing basic platform on screen
- Week 2 (9/21 - 9/27): Player moves around screen, player affected by gravity, 
- Week 3 (9/28 - 10/4): Player collides with platform, player can move between levels
- Week 4 (10/5 - 10/10): Debug and game testing

### Supplemental information and design documents:
#### Raylib - Documentation Resources
- https://www.raylib.com/
- https://github.com/raysan5/raylib/wiki/Using-raylib-with-Cpp
- https://github.com/raysan5/raylib/blob/master/CONVENTIONS.md 

### What finished MVP will NEED to do by the end of the spike to be a basis for next spike:
The MVP will need to include player movement, a working physics system, hitboxes for the platform(s), player hitbox and a level loading system. This will give us a good foundation to build upon for our next development spike.
