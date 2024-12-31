#pragma once

#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <math.h>

class PhysicsBall {
public:
  PhysicsBall(b2WorldId worldId, b2Vec2 position, float radius,
              sf::Color color);
  ~PhysicsBall();

  // Delete copy and move operations
  PhysicsBall(const PhysicsBall &other) = delete;
  PhysicsBall &operator=(const PhysicsBall &other) = delete;
  PhysicsBall(PhysicsBall &&other) noexcept = delete;
  PhysicsBall &operator=(PhysicsBall &&other) noexcept = delete;

  void draw(sf::RenderTarget &target) const;

  b2Vec2 getPosition() const { return position; }
  b2BodyId getBodyId() const { return bodyId; }
  void update();

private:
  float radius;
  sf::CircleShape ball;
  b2BodyId bodyId;
  b2Vec2 position;
  sf::Color color;
};

std::unique_ptr<PhysicsBall> createPhysicsBall(b2WorldId worldId,
                                               b2Vec2 position, float radius,
                                               sf::Color color);
