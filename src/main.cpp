#include "environment.hpp"
#include "physics_ball.hpp"
#include "physics_hex.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <box2d/box2d.h>

int main() {
  auto window = sf::RenderWindow(sf::VideoMode({1920, 1080}), "Hexagon Demo");
  window.setFramerateLimit(144);
  sf::Clock clock;

  b2WorldDef worldDef = b2DefaultWorldDef();
  worldDef.gravity = {0.0f, -10.0f};
  b2WorldId worldId = b2CreateWorld(&worldDef);

  // Draw a few hexagons in a row
  float radius = 1.0f;
  b2Vec2 initialPosition = {0.0f, 5.0f};
  sf::Color color = sf::Color::Yellow;
  std::vector<std::unique_ptr<PhysicsHex>> hexagons;

  for (int i = 0; i < 50; i++) {
    auto hex = createPhysicsHex(worldId, initialPosition, radius, color);
    hexagons.push_back(std::move(hex));
    initialPosition.x += radius * 2;
  }

  // Draw the bouncy ball
  float ballRadius = 0.5f;
  auto physicsBall =
      createPhysicsBall(worldId, {7.8f, 15.0f}, ballRadius, sf::Color::Red);

  const auto timeStep = 1.0f / 60.0f;

  while (window.isOpen()) {
    sf::Time elapsedTime = clock.restart();

    // Update physics
    b2World_Step(worldId, timeStep, 4);
    physicsBall->update();

    while (const auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();

      } else if (const auto *mouseButton =
                     event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButton->button == sf::Mouse::Button::Left) {
          auto mousePosition = mouseButton->position;
          auto worldPosition = Environment::pixelsToMeters(mousePosition);
          physicsBall->setPosition(worldPosition);
        }
      }

      else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Q) {
          window.close();
        }
      }
    }

    // Draw world
    window.clear();
    physicsBall->draw(window);
    for (auto &hexagon : hexagons) {
      hexagon->draw(window);
    }
    window.display();

    // Sleep until the next frame
    if (elapsedTime < sf::seconds(timeStep)) {
      sf::sleep(sf::seconds(timeStep) - elapsedTime);
    }
  }

  // Since we have a destructor which destroys the body, we need to be sure
  // to destroy the hexagons before destroying the world.
  hexagons.clear();
  physicsBall.reset();
  b2DestroyWorld(worldId);

  return 0;
}
