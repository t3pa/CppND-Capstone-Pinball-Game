#include "controller.h"
#include "SDL.h"
#include "flipper.h"

void Controller::HandleInput(bool &running, Ball &ball, Flipper &left, Flipper &right) const
{
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      running = false;
    }
    else if (e.type == SDL_KEYDOWN)
    {
      switch (e.key.keysym.sym)
      {
        case SDLK_SPACE:
          ball.Reset(BallInitialPosition);
          break;

        case SDLK_UP:
          break;

        case SDLK_DOWN:
          break;

        case SDLK_LEFT:
          left.Enable();
          break;

        case SDLK_RIGHT:
          right.Enable();
          break;
      }
    }
    else
    {
      left.Disable();
      right.Disable();
    }
  }
}