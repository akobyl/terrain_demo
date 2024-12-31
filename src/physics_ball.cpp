#include "physics_ball.hpp"
#include "environment.hpp"
#include <box2d/types.h>

PhysicsBall::PhysicsBall(b2WorldId worldId, b2Vec2 position, float radius,
                         sf::Color color)
    : radius(radius), position(position), color(color) {
  ball.setRadius(radius * Environment::SCALE);
  ball.setFillColor(color);
  ball.setFillColor(color);
  ball.setOrigin({radius * Environment::SCALE, radius * Environment::SCALE});
  ball.setPosition(Environment::metersToPixels(position));

  b2BodyDef ballBodyDef = b2DefaultBodyDef();
  ballBodyDef.type = b2_dynamicBody;
  ballBodyDef.position = position;
  bodyId = b2CreateBody(worldId, &ballBodyDef);
  b2ShapeDef ballShapeDef = b2DefaultShapeDef();
  ballShapeDef.density = 1.0f;
  ballShapeDef.friction = 0.3f;
  ballShapeDef.restitution = 0.5f;

  // The center off a b2Circle needs to be set to (0,0) since it is the local
  // center
  b2Circle ballCircle = {{0.0f, 0.0f}, radius};
  b2CreateCircleShape(bodyId, &ballShapeDef, &ballCircle);
}

void PhysicsBall::update() {
  position = b2Body_GetPosition(bodyId);
  ball.setPosition(Environment::metersToPixels(position));
}

void PhysicsBall::draw(sf::RenderTarget &target) const { target.draw(ball); }

std::unique_ptr<PhysicsBall> createPhysicsBall(b2WorldId worldId,
                                               b2Vec2 position, float radius,
                                               sf::Color color) {
  return std::make_unique<PhysicsBall>(worldId, position, radius, color);
}

PhysicsBall::~PhysicsBall() { b2DestroyBody(bodyId); }
