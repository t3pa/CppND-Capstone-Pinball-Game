#include "renderer.h"
#include <iostream>
#include <string>
#include <cmath>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)

    : screen_width(screen_width),
      screen_height(screen_height)
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Pinball Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer)
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer()
{
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Ball &ball)
{
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(sdl_renderer);

#ifndef TEXTURE
  // render the ball at its current position by drawing points
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF); // color: white
  SDL_Rect DestR;
  DestR.x = ball.GetPosition().first;
  DestR.y = ball.GetPosition().second;
  float width;
  int diameter = 2*ball.radius;
  float radius_squared = ball.radius * ball.radius;
  int y = 1 - ball.radius;
  for (; y<int(ball.radius); y++)
  {
    int start_x = int(-sqrt(radius_squared - y*y));
    int end_x   = int( sqrt(radius_squared - y*y));
    for (int x=start_x; x<end_x; x++)
    {
      SDL_RenderDrawPoint(sdl_renderer, DestR.x+x, DestR.y+y);
    }
  }
#else
  /* Rectangles for drawing which will specify source (inside the texture)
  and target (on the screen) for rendering our textures. */
  SDL_Rect SrcR;
  SDL_Rect DestR;

  SrcR.x = 0;
  SrcR.y = 0;
  SrcR.w = 80;
  SrcR.h = 80;

  DestR.x = ball.GetPosition().first;
  DestR.y = ball.GetPosition().second;
  DestR.w = 80;
  DestR.h = 80;

  //Render texture to screen
  SDL_RenderCopy(sdl_renderer, ball.GetTexture(), &SrcR, &DestR);
#endif
}

void Renderer::Render(Flipper &flipper)
{
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0xFF, 0xFF);
  SDL_RenderDrawLine(sdl_renderer, int(flipper.startpoint.first), int(flipper.startpoint.second),
                                   int(flipper.endpoint.first), int(flipper.endpoint.second));
  // draw bounding box
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawLine(sdl_renderer, int(flipper.startpoint.first), int(flipper.startpoint.second),
                                   int(flipper.startpoint.first), int(flipper.endpoint.second));
  SDL_RenderDrawLine(sdl_renderer, int(flipper.startpoint.first), int(flipper.startpoint.second),
                                   int(flipper.endpoint.first), int(flipper.startpoint.second));
  
}

void Renderer::UpdateWindowTitle(int score, int fps)
{
  std::string title{"Pinball Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
