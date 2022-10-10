#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "SDL.h"

// an x-y coordinate vector
typedef std::pair<float, float> Vector;

// Game physics constants, tweak by trial and error
const float GRAVITY = 0.14;
const float DAMPING_BOUNDARY = 0.60;  // damping at frame boundary
const float DAMPING_FALLING = 0.70; // damping when falling onto Flipper
const float DAMPING_FLIPPER = 1.70; // damping when hit by Flipper movement
const float COLLISION_TOLERANCE = 12.0; // proximity in pixels at which collision is signaled
const float FLIPPER_IMPULSE = 5.0; // velocity added by moving a Flipper
// Colors for Game elements
const SDL_Color ColorWhite = {255, 255, 255};
const SDL_Color ColorPurple = {255, 0, 255};
const SDL_Color ColorGreen = {0, 255, 0};
const SDL_Color ColorRed = {255, 0, 0};
// Positions of the Game elements in the Frame
const Vector BallInitialPosition = {200.0, 0.0};
const Vector BounceOnePosition = {100.0, 100.0};
const Vector BounceTwoPosition = {500.0, 200.0};

#endif