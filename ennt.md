# ENNT usage plan

We will use an ENTT registry to track components and a map<string, entt::entity> to track entities.

## The main game loop will have an update and a draw function.

### Update
The update function will take in the component registry, entity map and the current delta time.
it will then call the necessary functions on each of the components that need to be updated.

### Draw
The Draw function will take in the component registry and render each texture to the screen.
