# ECS Usage guidelines

## About the ECS
An entity control system or ECS, is a method of managing the state of a system through the composition of components in to entities which are them managed by different systems. For this project we are using the entt library: https://github.com/skypjack/entt.  

### The Registry
All entities and their associated components are stored in the registry. Once stored, components can be accessed anywhere that has access to the registry with a function called view which will be covered later in the document.

#### Creating the registry
```
// Create entt registry
entt::registry registry = entt::registry();
```

### Entities
Entities are just a group of associated components that represent the actual object.
Entities should have functions for creating, updating, and deleting them.

#### Adding an entity to the registry
```
// Add Player entity to the registry
entt::entity playerEnt = registry.create();
```
This function creates an entity playEnt which is a reference to the entity.

### Components
Components are the building blocks that come together to make entities.
    - Any struct data type can be a component.
    - Much like a table in a database, components should only contain data relevant to the component itself.

#### Adding a component to an entity
Components are added to the registry using the emplace function shown below.
```
// Add Player component to the entity
Player playerComponent;
registry.emplace<Player>(playerEnt, playerComponent);
```
This code creates an empty struct 'Player' of type 'PlayerComponent'. This is then added to the registry using the emplace function.
This function takes the component type in the <>, in this case the type is 'Player'. It also takes a reference to the target entity (PlayerEnt) and the component it self (playerComponent) as the arguments.

### Systems 
Systems are the functions that manage the entities in the registry. They all take in the registry as one of their arguments.
These functions can then access the relevant components using the registry.view() function. This function takes in a list of components and returns an iterable list of all entities that contain the specified components.  
Note this will only return entities that contain all of the requested components 

### Full code example
```
// Function to create the player entity
void CreatePlayer(entt::registry &registry) {
    TraceLog(LOG_TRACE, "Entering Function: CreatePlayer");
    TraceLog(LOG_INFO, "Creating Player Entity");
    
    // Add Player entity to the registry
    entt::entity playerEnt = registry.create();

    // Add Player component to the entity
    Player playerComponent;
    registry.emplace<Player>(playerEnt, playerComponent);


    // Load player sprites
    SpriteData cowSprite = SpriteData(LoadTextures({
            {"cowR", "assets/sprites/cowR.png"},
            {"cowL", "assets/sprites/cowL.png"}
        }),
        WHITE
    );
    cowSprite.SetTexture("cowR");
    // Add SpriteData component to the entity
    registry.emplace<SpriteData>(playerEnt, cowSprite);

    // Add Transform component to the entity
    Transform playerTransform = Transform{ {400.0f, 300.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {CHAR_WIDTH, CHAR_HEIGHT} };
    registry.emplace<Transform>(playerEnt, playerTransform);

    // Add PhysicsObject component to the entity
    PhysicsObject physics = PhysicsObject(1.0f, {0.0f, 0.0f});
    registry.emplace<PhysicsObject>(playerEnt, physics);

    // Add PlayerStats component to the entity
    PlayerStats stats = PlayerStats(MAX_HEALTH, MAX_IFRAMES, SPEED, JUMP_STRENGTH, GRAVITY);
    registry.emplace<PlayerStats>(playerEnt, stats);

    // Add the rest of the components needed for the player here
};
```