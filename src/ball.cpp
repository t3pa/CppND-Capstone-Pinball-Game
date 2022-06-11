#include "ball.h"
#include "renderer.h"

Ball::Ball(const std::size_t radius_, const SDL_Color color_,
           const std::size_t screen_width_, std::size_t screen_height_,
           Renderer &renderer)
    : radius(radius_),
      color(color_),
      screen_width(screen_width_),
      screen_height(screen_height_),
      position(300.0, 0.0),
      velocity(5.0, 3.5)
{
  //Load image at specified path
  std::string path("assets/ball2.bmp");
  SDL_Surface *surface = SDL_LoadBMP(path.c_str());
  if (surface == NULL)
  {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
  }
  else
  {
    //Create texture from surface pixels
    texture = SDL_CreateTextureFromSurface(renderer.GetRenderer(), surface);
    if (texture == NULL)
    {
      printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(surface);
  }
};

Vector Ball::GetPosition() const
{
  Vector v;
  v.first = position.first;
  v.second = position.second;
  return v;
}

void Ball::Update()
{
  float damping = 0.88;
  float gravity = 0.12;
  // update ball position
  position.first += velocity.first;
  // implement the ball bouncing off a screen boundary
  if (position.first > screen_width)
  {
    position.first = screen_width;
    velocity.first *= -1.0 * damping;
  }
  else if (position.first < 0.0)
  {
    position.first = 0.0;
    velocity.first *= -1.0 * damping;
  }
  position.second += velocity.second;
  if (position.second > screen_height)
  {
    position.second = screen_height;
    velocity.second *= -1.0 * damping;
  }
  else if (position.second < 0.0)
  {
    position.second = 0.0;
    velocity.second *= -1.0 * damping;
  }

  // update ball velocity by applying gravity
  velocity.second += gravity;
}