#include <iostream>
#include "controller.h"
#include "renderer.h"
#include "game.h"

int main()
{
  constexpr std::size_t kFramesPerSecond{70};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};

  Renderer renderer(kScreenWidth, kScreenHeight);
  Controller controller;
  Game game(kScreenWidth, kScreenHeight, renderer);
  std::cout << "Welcome to Pinball!\n";
  std::cout << "Use left and right arrow keys for Flipper control\n";
  std::cout << "Use Space bar for a new ball\n";
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Highscore: " << game.GetHighScore() << "\n";

  return 0;
}