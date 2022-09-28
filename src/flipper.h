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
  void Update(); // applies the changes scheduled through Enable() or Disable()
  bool WasEnabled(); // returns true when the Flipper was enabled in the previous iteration
  bool IsInBoundingBox(const Vector point); // checks whether point is within the bounding box of the Flipper
  bool IsColliding(const Vector point, Vector &collision_point); // checks whether point touches the line of the Flipper, if true returns linepoint
  float GetAngle();
  const Vector startpoint;
  Vector endpoint;

private:
  bool enabled; // true if the flipper is engaged (angled)
  bool enabled_next;
  Vector endpoint_enabled;  // the endpoint of the line when Flipper is enabled
  Vector endpoint_disabled; // the endpoint of the line when Flipper is disabled
  float gradient_enabled;
  float gradient_disabled;
  float gradient; // gradient of the line 
  const float fixedlength = 290; // length of the fixed segment  
  const float fixedangle;  // angle to horizontal at which flipper is pointing when disabled. positive: tilted down
  
};

#endif