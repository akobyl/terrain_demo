#pragma once

#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <math.h>

class PhysicsHex {
public:
  PhysicsHex(b2WorldId worldId, b2Vec2 position, float radius, sf::Color color);
  ~PhysicsHex();

  // Delete copy and move operations
  PhysicsHex(const PhysicsHex &other) = delete;
  PhysicsHex &operator=(const PhysicsHex &other) = delete;
  PhysicsHex(PhysicsHex &&other) noexcept = delete;
  PhysicsHex &operator=(PhysicsHex &&other) noexcept = delete;

  void draw(sf::RenderTarget &target) const;

  b2Vec2 getPosition() const { return position; }

private:
  float radius;
  sf::ConvexShape hexagon;
  b2BodyId bodyId;
  b2Vec2 position;
  sf::Color color;
};

std::unique_ptr<PhysicsHex> createPhysicsHex(b2WorldId worldId, b2Vec2 position,
                                             float radius, sf::Color color);
