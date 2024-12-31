#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

namespace Environment {
const float SCALE = 30.0f;
const auto HEIGHT = 1080;

/**
 * Converts pixel coordinates to Box2D meters.
 *
 * @param pixels A vector representing the position in pixels.
 * @return A b2Vec2 vector representing the position in meters.
 */
inline b2Vec2 pixelsToMeters(sf::Vector2f pixels) {
  return {pixels.x / SCALE, (HEIGHT - pixels.y) / SCALE};
}

inline b2Vec2 pixelsToMeters(sf::Vector2i pixels) {
  return {(float)pixels.x / SCALE, (HEIGHT - pixels.y) / SCALE};
}

/**
 * Converts Box2D meters to pixel coordinates.
 *
 * @param meters A b2Vec2 vector representing the position in meters.
 * @return A vector representing the position in pixels.
 */
inline sf::Vector2f metersToPixels(b2Vec2 meters) {
  return {meters.x * SCALE, HEIGHT - meters.y * SCALE};
}
} // namespace Environment

// TODO: add world id to environment
