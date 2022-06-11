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
  const Vector startpoint;
  Vector endpoint;

private:
  Vector endpoint_enabled;  // the endpoint of the line when Flipper is on
  Vector endpoint_disabled; // the endpoint of the line when Flipper is off

  bool on; // true if the flipper is engaged (angled)
  const float fixedlength = 100; // length of the fixed segment
  //const float fliplength = 30; // length of the flexible/angled segment
  const float fixedangle;  // 60 degrees in radians
  const float flipangle = 1.57;   // 90 degrees in radians
};

#endif