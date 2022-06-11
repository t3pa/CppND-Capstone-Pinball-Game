#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t screen_width, std::size_t screen_height, Renderer &renderer)
    : ball(25, ColorGray, screen_width, screen_height, renderer),
      flipper_left({30.0,screen_height-100.0}, 1.04),
      flipper_right({screen_width-30.0,screen_height-100.0}, -1.04),
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
    controller.HandleInput(running, flipper_left, flipper_right);
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

  ball.Update();
}

int Game::GetScore() const { return score; }
