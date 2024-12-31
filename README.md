# Terrain Demo

Creates a basic ground of hexagons with SFML and Box2D.  A ball can bounce around the ground and be moved with a click.

## Noteworthy notes

Converting between SFML and Box2D coordinates can be slightly confusing!  SFML uses pixels starting at the top left, and Box2D uses meters starting at the bottom left.

```cpp
inline b2Vec2 pixelsToMeters(sf::Vector2f pixels) {
  return {pixels.x / SCALE, (HEIGHT - pixels.y) / SCALE};
}
```

When creating balls or polygons, be careful about setting positions.  Some position values are actually the "local" position of the object, not where it is located in the world.  This is a hexagon:

```cpp
  // Create body definition
  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = b2_staticBody;

  // Body id is the handle to the body
  bodyId = b2CreateBody(worldId, &bodyDef);

  // Coordinates must be counter-clockwise, and in world-coordinates
  std::vector<b2Vec2> vertices(6);
  for (size_t i = 0; i < 6; i++) {
    float angle = static_cast<float>(i) * 2.0f * M_PI / 6;
    vertices[i] = {position.x + cos(angle) * radius,
                   position.y + sin(angle) * radius};
  }

  // Create a hull from the vertices
  b2Hull hull = b2ComputeHull(vertices.data(), 6);

  // Create a polygon from the hull
  b2Polygon hexPolygon = b2MakePolygon(&hull, 0.0f);

  // Create the shape definition (use defaults for static bodies)
  auto shapeDef = b2DefaultShapeDef();

  // Create the polygon shape
  b2CreatePolygonShape(bodyId, &shapeDef, &hexPolygon);
```


And this is a circle:

```cpp
  b2BodyDef ballBodyDef = b2DefaultBodyDef();
  ballBodyDef.type = b2_dynamicBody;

  // Set position in world coordinates
  ballBodyDef.position = position;

  bodyId = b2CreateBody(worldId, &ballBodyDef);
  b2ShapeDef ballShapeDef = b2DefaultShapeDef();
  ballShapeDef.density = 1.0f;
  ballShapeDef.friction = 0.3f;
  ballShapeDef.restitution = 0.5f;

  // local center, not world coordinates!!
  b2Circle ballCircle = {{0.0f, 0.0f}, radius};
  b2CreateCircleShape(bodyId, &ballShapeDef, &ballCircle);
```

And be sure to use `float` for all box2d values!
