#ifndef FLIPPER_H
#define FLIPPER_H

//#include <vector>
#include "definitions.h"

// a Flipper consists of two line segments, one of which is movable (the flipping part)
class Flipper
{
public:
  Flipper(const Vector startpoint, const float fixedangle_);
  void Enable();
  void Disable();
  bool IsInBoundingBox(const Vector point); // checks whether point is within the bounding box of the Flipper
  bool IsColliding(const Vector point); // checks whether point touches the line of the Flipper
  float GetAngle();
  const Vector startpoint;
  Vector endpoint;

private:
  bool enabled; // true if the flipper is engaged (angled)
  Vector endpoint_enabled;  // the endpoint of the line when Flipper is enabled
  Vector endpoint_disabled; // the endpoint of the line when Flipper is disabled
  float gradient_enabled;
  float gradient_disabled;
  float gradient; // gradient of the line 
  const float fixedlength = 200; // length of the fixed segment  
  const float fixedangle;  // angle to horizontal at which flipper is pointing when disabled. positive: tilted down
  const float collision_tolerance = 10.0; // proximity in pixels at which collision is signaled
};

#endif