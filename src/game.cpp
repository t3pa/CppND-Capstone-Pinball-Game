#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t screen_width, std::size_t screen_height, Renderer &renderer)
    : ball(25, ColorGray, screen_width, screen_height, renderer),
      flipper_left({0.0,screen_height-100.0}, 1.04), // 1.04 is 60 degrees in radians
      flipper_right({screen_width-1.0,screen_height-100.0}, -1.04),
      screen_width(screen_width),
      screen_height(screen_height),
      engine(dev())
{
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, ball, flipper_left, flipper_right);
    Update();
    renderer.Render(ball);
    renderer.Render(flipper_left);
    renderer.Render(flipper_right);
    renderer.UpdateScreen();

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update()
{
  Vector ball_position = ball.GetPosition();
  Vector ball_velocity = ball.GetVelocity();
  ball_position.second += ball.radius;  // as an approximation, we take the bottom point of the Ball as the collision contact point.
  ball.Update(); // update movement only subject to frame boundaries
  
  // update ball movement subject to flipper positions
  if (ball_velocity.second > 0.0) // we only consider cases where the ball is falling down
  {
    // two-phase approach for Flipper interaction: first check if Ball is within bounding box 
    // of the Flipper, then if Ball actually touches the Flipper line.
    if (flipper_left.IsInBoundingBox(ball_position))
    {   
      if (flipper_left.IsColliding(ball_position))
      {
        ball.Collide(flipper_left.GetAngle());
        std::cout << "Collide left x=" << ball_position.first << "\n";
      }    
    }
    if (flipper_right.IsInBoundingBox(ball_position))
    {
      if (flipper_right.IsColliding(ball_position))
      {
        ball.Collide(flipper_right.GetAngle());
        std::cout << "Collide right x=" << ball_position.first << "\n";
      }
    }
  }
}

int Game::GetScore() const { return score; }
