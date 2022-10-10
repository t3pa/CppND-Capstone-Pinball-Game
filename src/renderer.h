#ifndef RENDERER_H
#define RENDERER_H

#include "definitions.h"
#include "ball.h"
#include "flipper.h"

class Renderer
{
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  SDL_Renderer *GetRenderer() { return sdl_renderer; };
  void ClearScreen();
  void UpdateScreen() {SDL_RenderPresent(sdl_renderer);}
  void Render(const Ball &ball); // renders the Ball on the screen
  void Render(const Flipper &flipper); // renders the Flipper on the screen
  void UpdateWindowTitle(int score, int highscore, int fps);

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif