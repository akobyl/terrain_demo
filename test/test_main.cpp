#include "physics_ball.hpp"
#include "physics_hex.hpp"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <gtest/gtest.h>

TEST(PhysicsTest, BallLandsOnHex) {
  // Create Box2D world
  b2WorldDef worldDef = b2DefaultWorldDef();
  worldDef.gravity = {0.0f, -9.81f};
  b2WorldId worldId = b2CreateWorld(&worldDef);
  ASSERT_TRUE(b2World_IsValid(worldId)) << "Failed to create valid Box2D world";

  // Create hex at bottom
  auto hex = createPhysicsHex(worldId, {0.0f, 0.0f}, 1.0f, sf::Color::Blue);

  // Create ball above hex
  auto ball = createPhysicsBall(worldId, {0.0f, 5.0f}, 0.5f, sf::Color::Red);
  ASSERT_TRUE(ball != nullptr) << "Failed to create ball";
  ASSERT_TRUE(b2Body_IsValid(ball->getBodyId())) << "Invalid ball body";

  // Initial position check
  b2Vec2 startPos = b2Body_GetPosition(ball->getBodyId());
  EXPECT_FLOAT_EQ(startPos.y, 5.0f);

  float timeStep = 1.0f / 60.0f;
  for (int i = 0; i < 300; i++) {
    b2World_Step(worldId, timeStep, 8);
    ball->update();
  }

  // Check final position - ball should be resting on hex
  b2Vec2 finalPos = b2Body_GetPosition(ball->getBodyId());
  // For hex radius 1.0, height to edge is √3/2 ≈ 0.866
  // Plus ball radius 0.5
  EXPECT_NEAR(finalPos.y, 1.366f, 0.1f) << "Ball y-position incorrect";
  EXPECT_NEAR(finalPos.x, 0.0f, 0.1f) << "Ball x-position incorrect";

  b2Vec2 velocity = b2Body_GetLinearVelocity(ball->getBodyId());
  EXPECT_NEAR(velocity.y, 0.0f, 0.2f);
}

TEST(PhysicsTest, BallBouncesOffHexSide) {
  // Create Box2D world
  b2WorldDef worldDef = b2DefaultWorldDef();
  worldDef.gravity = {0.0f, -9.81f};
  b2WorldId worldId = b2CreateWorld(&worldDef);
  ASSERT_TRUE(b2World_IsValid(worldId)) << "Failed to create valid Box2D world";

  // Create hex at origin
  auto hex = createPhysicsHex(worldId, {0.0f, 0.0f}, 1.0f, sf::Color::Blue);

  // Create ball above and to the right of hex
  auto ball = createPhysicsBall(worldId, {1.0f, 3.0f}, 0.5f, sf::Color::Red);
  ASSERT_TRUE(ball != nullptr) << "Failed to create ball";
  ASSERT_TRUE(b2Body_IsValid(ball->getBodyId())) << "Invalid ball body";

  float timeStep = 1.0f / 60.0f;
  for (int i = 0; i < 180; i++) {
    b2World_Step(worldId, timeStep, 8);
    ball->update();
  }

  // Check final position - ball should be to the right and below the hex
  b2Vec2 finalPos = b2Body_GetPosition(ball->getBodyId());
  EXPECT_GT(finalPos.x, 1.0f)
      << "Ball should be to the right of starting position";
  EXPECT_LT(finalPos.y, 0.0f) << "Ball should be below the hex";

  b2Vec2 velocity = b2Body_GetLinearVelocity(ball->getBodyId());
  EXPECT_LT(velocity.y, 0.0f) << "Ball should still be falling";
}
