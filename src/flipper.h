#ifndef FLIPPER_H
#define FLIPPER_H

#include "definitions.h"

// a Flipper consists of one line segment, one point of which is movable (the flipping part)
class Flipper
{
public:
  Flipper(const Vector startpoint, const float fixedangle_);
  void Enable(); // schedules the enabling for next iteration
  void Disable();  // schedules the disabling for next iteration
  void Update(); // applies the changes scheduled through Enable() or Disable()
  bool WasEnabled() const; // returns true when the Flipper was enabled in the previous iteration
  bool IsInBoundingBox(const Vector point) const; // checks whether point is within the bounding box of the Flipper
  bool IsColliding(const Vector point, Vector &collision_point) const; // checks whether point touches the line of the Flipper, if true returns linepoint
  float GetAngle() const;

public:
  const Vector startpoint;
  Vector endpoint; // is not const because that's the moving point of the line

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