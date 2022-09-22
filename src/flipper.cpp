#include "flipper.h"

Flipper::Flipper(const Vector startpoint_, const float fixedangle_)
 : startpoint (startpoint_),
   fixedangle (fixedangle_),
   enabled (false)
{
  // endpoint is at lower right of startpoint
  endpoint_disabled = {startpoint_.first + fixedlength*sin(fixedangle),
                      startpoint_.second + fixedlength*cos(fixedangle)};

  // endpoint is at upper right of startpoint
  endpoint_enabled = {startpoint_.first + fixedlength*sin(fixedangle),
                      startpoint_.second - fixedlength*cos(fixedangle)};
    
  // calculate gradient m = dy/dx    
  gradient_enabled  = (endpoint_enabled.second - startpoint.second)  / (endpoint_enabled.first - startpoint.first); 
  gradient_disabled = (endpoint_disabled.second - startpoint.second) / (endpoint_disabled.first - startpoint.first);
}
void Flipper::Enable()
{  
  endpoint = endpoint_enabled;
  gradient = gradient_enabled;
  enabled = true;
  
}

void Flipper::Disable()
{
  endpoint = endpoint_disabled;
  gradient = gradient_disabled;
  enabled = false;
}

float Flipper::GetAngle()
{
  if (!enabled)
    return fixedangle;
  else
    return -fixedangle;
}

bool Flipper::IsInBoundingBox(const Vector point)
{
  if ((startpoint.first < endpoint.first && point.first > startpoint.first && point.first < endpoint.first) // horizontal condition for "left" flipper
   || (startpoint.first > endpoint.first && point.first < startpoint.first && point.first > endpoint.first)) // horizontal condition for "right" flipper
  {
    // when disabled, endpoint marks the lower right corner of the bounding box
    if (!enabled && point.second > startpoint.second && point.second < endpoint.second)
      return true;
    // when enabled, endpoint marks the upper right corner of the bounding box
    else if (enabled && point.second > endpoint.second && point.second < startpoint.second)
      return true;  
  }
  return false; 
}

bool Flipper::IsColliding(const Vector point)
{
  if (startpoint.first < endpoint.first) // "left" flipper
  {
    float dx = point.first - startpoint.first;  // x-coordinate of the point relative to startpoint
    float dy = dx * gradient;                   
    float line_y = startpoint.second + dy;      // y-coordinate of the line at this x
    if ((line_y > point.second && (line_y - point.second < collision_tolerance))) // does the point almost touch the line?
    // || (line_y < point.second && (point.second - line_y < collision_tolerance)))
   return true;
  }
  else if (startpoint.first > endpoint.first) // "right" flipper
  {
    float dx = point.first - startpoint.first;  // x-coordinate of the point relative to startpoint
    float dy = dx * gradient;                   
    float line_y = startpoint.second + dy;      // y-coordinate of the line at this x
    if ((line_y > point.second && (line_y - point.second < collision_tolerance))) // does the point almost touch the line?
    // || (line_y < point.second && (point.second - line_y < collision_tolerance)))
   return true;
  }
  return false;  
}
