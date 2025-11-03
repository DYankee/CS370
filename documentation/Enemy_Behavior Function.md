# Enemy Behavior
Enemy_behavior is the component that controls each enemies behavior. When each enemy is constructed it will need one of these as part of its components.

## Update function
The main main purpose of this component is to provide a pointer to an update function for the enemy. The function itself can be any void function that takes in the following:
    - entt::registry&
    - float
    - entt::entity

#### Example Code
Example update function
```
void TestUpdateFunc(entt::registry &registry, float dt, entt::entity enemy){
    TraceLog(LOG_TRACE, "Entering TestUpdateFunc");

    // Get components from enemy entity
    auto [pos, physics, stats] = registry.get<Transform, PhysicsObject, EnemyStats>(enemy);

    pos.translation.x += stats.enemySpeed * dt;
    TraceLog(LOG_TRACE, "Exiting TestUpdateFunc");
}
```
Add function to Enemy_behavior Function
```
    // Add update function
    Enemy_behavior behavior = TestUpdateFunc; // note the lack of () at the end of the function because its just a pointer to the function definition 
    registry.emplace<Enemy_behavior>(enemyEnt, behavior);
```

### Why
By making the enemy update function a component of the entity we can potentially assign each enemy a unique function to control its behavior. For example we can have different types of enemy that each get their own update functions and behavior