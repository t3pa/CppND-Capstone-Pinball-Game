#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t screen_width, std::size_t screen_height, Renderer &renderer)
    : ball(30, BallInitialPosition, ColorWhite, screen_width, screen_height, renderer),
      bounce_one(40, BounceOnePosition, ColorGreen, screen_width, screen_height, renderer),
      bounce_two(40, BounceTwoPosition, ColorRed, screen_width, screen_height, renderer),
      flipper_left({0.0,screen_height-200.0}, 1.3), // 1.04 is 60 degrees in radians
      flipper_right({screen_width-1.0,screen_height-200.0}, -1.3),
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
    renderer.ClearScreen();
    renderer.Render(ball);
    renderer.Render(bounce_one);
    renderer.Render(bounce_two);
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
      renderer.UpdateWindowTitle(score, highscore, frame_count);
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
  
    
  // update ball movement subject to flipper positions
  // first check if Flipper was moved
  if (flipper_left.WasEnabled())
  {
     if (flipper_left.IsInBoundingBox(ball_position))
     {
       if (ball_position.second < flipper_left.endpoint.second) // Flipper was below the Ball?
       {         
         ball.VerticalImpulse();
         //std::cout << "Collide flip L x=" << ball_position.first << "\n";
       }
     }    
  }    
  else if (flipper_right.WasEnabled())
  {
    if (flipper_right.IsInBoundingBox(ball_position))
     {
       if (ball_position.second < flipper_right.endpoint.second) // Flipper was below the Ball?
       {         
         ball.VerticalImpulse();
         //std::cout << "Collide flip R x=" << ball_position.first << "\n";
       }
     }    
  }
  // else check if ball fell onto Flipper
  else if (ball_velocity.second > 0.0) // we only consider cases where the ball is falling down
  {
    // two-phase approach for Flipper interaction: first check if Ball is within bounding box 
    // of the Flipper, then if Ball actually touches the Flipper line.
    Vector collision_point;
    if (flipper_left.IsInBoundingBox(ball_position)
    && flipper_left.IsColliding(ball_position, collision_point))
      {
        //std::cout << "Collide left " << std::flush; 
        ball.Collide(flipper_left.GetAngle(), DAMPING_FALLING);        
        ball.Update(GRAVITY, DAMPING_BOUNDARY, collision_point.second-ball.radius); // update movement only subject to frame boundaries
        //std::cout << " ball.x= "<< ball_position.first << " ball.y= "<< ball_position.second << "\n";
      }    
    
    else if (flipper_right.IsInBoundingBox(ball_position)
    && flipper_right.IsColliding(ball_position, collision_point))
      {
        //std::cout << "Collide right " << std::flush;
        ball.Collide(flipper_right.GetAngle(), DAMPING_FALLING);
        ball.Update(GRAVITY, DAMPING_BOUNDARY, collision_point.second-ball.radius); // update movement only subject to frame boundaries
        //std::cout << " ball.x= "<< ball_position.first << " ball.y= "<< ball_position.second << "\n";
      }    
    else
      ball.Update(GRAVITY, DAMPING_BOUNDARY, screen_height); // update movement only subject to frame boundaries
  }
  else
    ball.Update(GRAVITY, DAMPING_BOUNDARY, screen_height);
  if (ball.Collide(bounce_one))
  {
    bounce_one.color = ColorPurple;
    score += 100;    
  }
  else
    bounce_one.color = ColorGreen;    
  if (ball.Collide(bounce_two))
  {
    bounce_two.color = ColorPurple;
    score += 100;    
  }
  else
    bounce_two.color = ColorRed;
  if (score > highscore)
    highscore = score;
  if (!ball.IsAlive())
    score = 0;
  flipper_left.Update();
  flipper_right.Update();
}

int Game::GetScore() const { return score; }
