#ifndef BALL_H
#define BALL_H

#include "definitions.h"
class Renderer;

class Ball
{
public:
  Ball(const std::size_t radius_, const SDL_Color color_,
       const std::size_t screen_width_, std::size_t screen_height_,
       Renderer &renderer);

  ~Ball() { SDL_DestroyTexture(texture); }

  SDL_Texture *GetTexture() { return texture; }
  void Update();                        // updates position and velocity, taking into account gravity
  void Collision(const Vector surface); // calculates the collision of Ball against a surface
  Vector GetPosition() const;

  const SDL_Color color; // color of the ball
  const std::size_t radius;    // radius of the ball

private:
  const std::size_t screen_width;
  const std::size_t screen_height;
  SDL_Texture *texture = NULL;
  Vector position; // first is x-position, second is y-position
  Vector velocity; // velocity vector, first is x-direction, second is y-direction
};

#endif