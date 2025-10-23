## Spike 2 Plan Document - Group 7: Milksong

## Cycle Intent
For this spike, we want the player to be able to complete at least one playable level, including the ability to fight enemies within it. Additionally, we want the game’s interactions with the player to be more polished, such as with collisions and asset rendering, as well as organizing the code and utilizing the entity systems to make future development much easier.


## Features and Responsibility:
- Write tests for asset loading (Zack)
Design and implement tests that check if functions that load assets are working correctly
Loop through each asset type and make sure it can be loaded and modified by its associated  functions

- Implement ECS system (Zack)
Refactor existing code into components, entities, and systems
Write documentation for the usage of the system

- Add detailed logging to function calls and state changes(Zack)
Create guidelines for logging
Add logging to existing code base based on guidelines

- Collision improvement (Nick)
Bug test and find out whats causing wonky collisions
Player getting stuck into the ground/walls
Make collisions and hitboxes make more sense visually 

- Organize code with separate classes and functions (Alaina)
Organize everything so we are no longer working on one single main file

- Add enemy entities (Alaina)
Create enemy entity and required functions

- Implement attack system for both player and enemy(Nick)
Make enemy entity chase after player
Give enemy hitboxes so they can damage the player
Make player take damage when colliding with the enemy
Give player attack button and functionality 
Make enemy take damage when attacked by player
Make enemy die when health becomes 0 (Kent)
Make player die when health becomes 0 and end the game or respawn the player (Kent)

- Implement player stat system (Nick)
Give player upgradable health stat
Give player upgradable attack stat

- Introduction menu with working Start button (Kent)
Starting menu on game load. Has “Start” button to press and enter game

- Implementing sprite animations (Kent)
Player cow has movement sprite animation cycles

- More general art assets for what is needed (Kent)
Art for second stage and possible in-game items

## Architectural decisions of required systems and how they interact:
All entities will be composed of a set of components
Entities will be managed by different systems related to their function.

## Schedule of now and between presentation day (10/10/25):
Week 8 (10/15 - 10/20): 
Plan out cycle two. Organize into separate classes and functions
Implement working ECS system (Zack)

Week 9 (10/20 - 10/26): 
Flesh out ECS system and create usage documentation (Zack)
Starting menu 
Fix collisions 
Make player stats

Week 10 (10/27 - 11/2): 
Create Enemy entity
Create asset loading tests (Zack)
Implement enemy and player attack systems 

Week 11(11/3 - 11/6): 
Presentation week finish up last needed things

## Supplemental information and design documents:
Raylib - Documentation Resources
https://www.raylib.com/
https://github.com/raysan5/raylib/wiki/Using-raylib-with-Cpp
https://github.com/raysan5/raylib/blob/master/CONVENTIONS.md 
https://github.com/luphi/raytmx

## What project will NEED to do by the end of the spike to be a basis for next spike:
Implement ECS system
Write tests for asset loading
Add enemy entities
Organize code with separate classes and functions 
Implement attack system for both player and enemy
Implement player stat system 
Introduction of menu with working Start button

