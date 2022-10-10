#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "ball.h"
#include "flipper.h"

class Game
{
public:
  Game(std::size_t screen_width, std::size_t screen_height, Renderer &renderer);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetHighScore() const;

private:
  const std::size_t screen_width;
  const std::size_t screen_height;
  Ball ball;
  Ball bounce_one;
  Ball bounce_two;
  Flipper flipper_left;
  Flipper flipper_right;
  int score{0};
  int highscore{0};

  void Update(); // the main Game logic
};

#endif