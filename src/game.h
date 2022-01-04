#ifndef GAME_H
#define GAME_H

#include <random>
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
  int GetScore() const;

private:
  const std::size_t screen_width;
  const std::size_t screen_height;

  Ball ball;
  Flipper flipper_left;
  Flipper flipper_right;

  std::random_device dev;
  std::mt19937 engine;

  int score{0};

  void Update();
};

#endif