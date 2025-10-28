# ECS Usage guidelines

## About the ECS
An entity control system or ECS, is a method of managing the state of a system through the composition of components into entities which are them managed by different systems. For this project we are using the entt library: https://github.com/skypjack/entt.  

### The Registry
All entities and their associated components are stored in the registry. Once stored, components can be accessed anywhere that has access to the registry with a function called view which will be covered later in the document.
The registry also has additional functionality like adding listeners to entities and saving the registry state so it can be loaded later (Possible save game implementation?). The documentation for ENTT can be found here: https://github.com/skypjack/entt/wiki/Entity-Component-System 

#### Creating the registry
```
// Create entt registry
entt::registry registry = entt::registry();
```

### Entities
Entities are just a group of associated components that represent the actual object.
Entities should have functions for creating, updating, and deleting them.
All distinct entity types should be created with an empty struct as one of its components for tagging. 
For example, all enemy entities should have an empty struct called 'Enemy' that could later be used to access specific types of entity.

#### Adding an entity to the registry
Entities are added to the registry using the registry.create function shown below.
```
// Add Player entity to the registry
entt::entity playerEnt = registry.create();
```
This function creates an entity playEnt which is a reference to the entity.

### Components
Components are the building blocks that come together to make entities. Any struct data type can be a component.
Much like a table in a database, components should only contain data relevant to the component itself. 
The player entity for example should not have a component that store position data of another entity.

#### Adding a component to an entity
Components are added to the registry using the emplace function shown below.
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
This code creates an empty struct 'Player' of type 'PlayerComponent'. This is then added to the registry using the emplace function.
This function takes the component type in the <>, in this case the type is 'Player'. It also takes a reference to the target entity (PlayerEnt) and the component it self (playerComponent) as the arguments.

### Systems 
Systems are the functions that manage the entities in the registry. They all take in the registry as one of their arguments (may simplify this to be automatic later).
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

## Usage guidelines

### Views
The main reason we pass the registry to functions it so we have access to views. Views are how you view and interact with components in the registry.
Think of a view as a database query. It takes in a list of components and returns a iterable list of all entities that contain at least all of the components listed.
#### Creating a view
```
entt::view view = registry.view<Transform, PhysicsObject>();
```
Using the tags I mentioned earlier we can select just the player entity by adding the 'Player' component to our list like so:
```
entt::view view = registry.view<Player, Transform, PhysicsObject>();
```
This will return a view with only entities with all 3 components which should only be one.

#### Using a view
There are a couple ways you can use a view to interact with the components in it.
```
for(entt::entity entity: view) {
    // a component at a time ...
    &Transform pos = view.get<Transform>(entity);
    &PhysicsObject phys = view.get<PhysicsObject>(entity);

    // ... multiple components ...
    auto [pos, phys] = view.get<Transform, PhysicsObject>(entity);

    // ... all components at once
    auto [pos, vel] = view.get(entity);
}
```

#### Combining the Two
It's also possible to combine these two steps into one using the each function
```
registry.view<Player, Transform, PhysicsObject>().each([dt, &registry](Transform &transform, PhysicsObject &physics){
    // You can then freely interact with  
    });
```
Note the 'dt' and '&registry' variables passed to the loop in the [] this allows us access to the variables inside the loop.
This can be used to create nested views which have access to multiple components
```
registry.view<Player, Transform, PhysicsObject>().each([&registry, dt](Transform &transform, PhysicsObject &physics){
    registry.view<Map, TmxMap>().each([&physics, &transform, dt](TmxMap &map) {
        // You can access components from both entities here
    });
});
```
