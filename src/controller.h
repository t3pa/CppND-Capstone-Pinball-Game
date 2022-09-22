#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ball.h"
#include "flipper.h"

class Controller
{
public:
  void HandleInput(bool &running, Ball &ball, Flipper &left, Flipper &right) const;

private:
  void EnableFlipper(Flipper &flipper) const;
};

#endif