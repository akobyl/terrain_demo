#include "physics_hex.hpp"
#include "environment.hpp"
#include <box2d/box2d.h>
#include <box2d/collision.h>
#include <box2d/types.h>

PhysicsHex::PhysicsHex(b2WorldId worldId, b2Vec2 position, float radius,
                       sf::Color color)
    : radius(radius), position(position), color(color) {

  // Create SFML visual
  hexagon.setPointCount(6);
  for (int i = 0; i < 6; i++) {
    float angle = static_cast<float>(i) * 2.0f * M_PI / 6;
    hexagon.setPoint(i, sf::Vector2f(Environment::SCALE * cos(angle),
                                     Environment::SCALE * sin(angle)));
  }
  hexagon.setFillColor(color);
  hexagon.setOutlineColor(sf::Color::Black);
  hexagon.setOutlineThickness(1.0f);
  hexagon.setPosition(Environment::metersToPixels(position));

  // Create Box2D physics
  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = b2_staticBody;
  bodyId = b2CreateBody(worldId, &bodyDef);

  std::vector<b2Vec2> vertices(6);
  for (size_t i = 0; i < 6; i++) {
    float angle = static_cast<float>(i) * 2.0f * M_PI / 6;
    vertices[i] = {position.x + cos(angle) * radius,
                   position.y + sin(angle) * radius};
  }

  b2Hull hull = b2ComputeHull(vertices.data(), 6);
  b2Polygon hexPolygon = b2MakePolygon(&hull, 0.0f);
  auto shapeDef = b2DefaultShapeDef();
  b2CreatePolygonShape(bodyId, &shapeDef, &hexPolygon);
}

std::unique_ptr<PhysicsHex> createPhysicsHex(b2WorldId worldId, b2Vec2 position,
                                             float radius, sf::Color color) {
  return std::make_unique<PhysicsHex>(worldId, position, radius, color);
}

PhysicsHex::~PhysicsHex() { b2DestroyBody(bodyId); }

void PhysicsHex::draw(sf::RenderTarget &target) const { target.draw(hexagon); }
