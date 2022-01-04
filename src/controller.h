#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "flipper.h"

class Controller
{
public:
  void HandleInput(bool &running, Flipper &left, Flipper &right) const;

private:
  void EnableFlipper(Flipper &flipper) const;
};

#endif