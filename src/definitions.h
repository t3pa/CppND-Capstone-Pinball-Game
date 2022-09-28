#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <utility>
#include <string>

#include "SDL.h"

// an x-y coordinate vector
typedef std::pair<float, float> Vector;

//class Constants
//{
const float GRAVITY = 0.14;
const float DAMPING_BOUNDARY = 0.60;
const float DAMPING_FALLING = 0.70;
const float DAMPING_FLIPPER = 1.70;
const float COLLISION_TOLERANCE = 15.0; // proximity in pixels at which collision is signaled
const SDL_Color ColorGray = {128, 128, 128};
//};

#endif