## CS370 Project Overview Document						    

### What is it?
Video Game (Action Platformer)

### Project Name: (Work in progress)
- Polyester Melody
- jean jingle
- Denim dance

### Team Members:
- Nicholas Decinto	-	Decintn@sunypoly.edu
- Zachary Geary	- 	gearyz@sunypoly.edu
- Kent Palabon		- 	palabok@sunypoly.edu
- Alaina Sabo		- 	saboa@sunypoly.edu

### Project Description:
We are planning on making a 2d action platformer. Our main users will be people who enjoy playing platformer video games. The player will be able to explore levels, fight/kill enemies, find and use items, and defeat bosses. We will do this using C++ with the raylib library. 

### Elevator pitch:
Silksong but even more indie.

### Core features
- Player Attack/Movement:
    - Player can move around, jump and collide with objects
    - Player can hit and DMG enemies
- Enemy Attack/Movement
    - Enemies can attack and DMG Player unit
    - Enemies move based on predefined behavior
- Map loading 
    - Player can move between maps that load and unload
- Items
    - Usable items for the players to pick up
- Bosses
    - Extra hard enemies with special abilities. 

### Tech Architecture
- Back-end: C++
    - All members of the team are familiar with the language.
- Front-end: Raylib
    - Professor suggestion
- High-level Architecture:
    - Basic game loop using the Raylib while running function to periodically call an update and render function.
    - Simple entity system to manage game elements and their functions.

### Team Roles and Responsibilities
- Architectural Lead: Alaina Sabo 
    - Coordinating and assisting with back-end and front-end development, ensuring that the different parts of the project are properly integrated with each other.
- DevOps Lead: Zachary Geary
    - Implementing build systems, writing tests and documenting code. Helping with code/design where needed.
- Front-End Lead: Kent Palabon
    - Implementing art, animations, and level design. Ensures these UI/UX elements are incorporated into the project, while working with the back-end.
- Back-End Lead: Nick Decinto
    - Implementing back end architecture such as physics system, player and enemy movement, items, and attack/DMG systems. Working with the front-end lead ensuring art is effectively implemented into the frame system.
