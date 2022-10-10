#include "ball.h"
#include "renderer.h"
#include <iostream>

Ball::Ball(const std::size_t radius_, const Vector position_, const SDL_Color color_,
           const std::size_t screen_width_, std::size_t screen_height_,
           Renderer &renderer)
    : radius(radius_),
      color(color_),
      screen_width(screen_width_),
      screen_height(screen_height_),
      position(position_),
      velocity(5.0, 5.5),
      alive(true)
{
  #ifdef TEXTURE
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
  #endif
};

void Ball::Reset(const Vector position_)
{
  position = position_;
  velocity.first = 5.0;
  velocity.second = 5.5;
  alive = true;
}

Vector Ball::GetPosition() const
{
  return position;
}

Vector Ball::GetVelocity() const
{
  return velocity;
}

void Ball::Update(float gravity, float damping, float max_y)
{
  if (!alive)
    return;
  // update ball position
  position.first += velocity.first;
  position.second += velocity.second;
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
  if (position.second > screen_height)
  {
    position.second = screen_height;
    velocity.first = velocity.second = 0.0;
    alive = false; // Ball has fallen out of bounds
  }
  else if (position.second > max_y)
  {
    position.second = max_y;
    velocity.second *= -1.0 * damping;
  }
  else if (position.second < 0.0)
  {
    position.second = 0.0;
    velocity.second *= -1.0 * damping;
  }
  // update ball vertical velocity by applying gravity
  velocity.second += gravity;
}

void Ball::VerticalImpulse()
{
  if (velocity.second > 0.0) // impulse direction is always up
     velocity.second *= -1.0;
  velocity.second -= FLIPPER_IMPULSE; // increase "up" velocity
}

// to emulate the Ball colliding with a line,
// we pretend the Ball collides with a horizontal line (which inverts its y-velocity)
// and then rotate the velocity vector by the actual angle of the line versus the horizontal.
void Ball::Collide(float angle, float damping)
{
  velocity.second *= -1.0 * damping;
  Vector new_velocity;
  new_velocity.first  = velocity.first*cos(angle) - velocity.second*sin(angle);
  new_velocity.second = velocity.first*sin(angle) + velocity.second*cos(angle);
  velocity = new_velocity;
}

// returns true if this Ball and other Ball are colliding (bounding boxes are touching)
// calculates the collision angle between the Ball centers
// and updates this Ball velocity accordingly
bool Ball::Collide(const Ball other)
{
  Vector other_position = other.GetPosition();
  bool horizontal_smaller = position.first < other_position.first;
  bool vertical_smaller = position.second < other_position.second;
  bool horizontal_overlap;
  bool vertical_overlap;
  // first we check if the bounding boxes of this Ball and the other Ball overlap
  if (horizontal_smaller)
    horizontal_overlap = (position.first+radius > other_position.first-other.radius);
  else
    horizontal_overlap = (position.first-radius < other_position.first+other.radius);
  if (vertical_smaller)
    vertical_overlap = (position.second+radius > other_position.second-other.radius);
  else
    vertical_overlap = (position.second-radius < other_position.second+other.radius);
  if (horizontal_overlap && vertical_overlap)
  {
     //std::cout << "Collide ball x=" << position.first << "\n " ;//<< std::flush;
     // now we construct a triangle where the hypotenuse connects the two centers of the Balls
     float deltax, deltay, hypotenuse;
     if (horizontal_smaller)
       deltax = other_position.first - position.first;
     else
       deltax = position.first - other_position.first;
     if (vertical_smaller)
       deltay = other_position.second - position.second;
     else
       deltay = position.second - other_position.second;

     hypotenuse = sqrt(deltax*deltax + deltay*deltay);
     float collision_angle = asin(deltay / hypotenuse);
     if (horizontal_smaller)
       collision_angle = M_PI - collision_angle;
     if (vertical_smaller)
       collision_angle = -collision_angle;
     //std::cout << "Collide ball x=" << position.first << " angle=" << (collision_angle/(2*M_PI))*360.0 << "\n " ;//<< std::flush;

    float angle = collision_angle+M_PI;
    Vector new_velocity;
    new_velocity.first  = velocity.first*cos(angle) - velocity.second*sin(angle);
    new_velocity.second = velocity.first*sin(angle) + velocity.second*cos(angle);
    velocity = new_velocity;
    return true;
  }
  else
    return false;

}