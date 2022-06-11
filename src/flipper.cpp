#include "flipper.h"

Flipper::Flipper(const Vector startpoint_, const float fixedangle_)
 : startpoint (startpoint_),
   fixedangle (fixedangle_),
   on (false)
{
  endpoint_disabled = {startpoint_.first + fixedlength*sin(fixedangle),
                      startpoint_.second + fixedlength*cos(fixedangle)};

  endpoint_enabled = {startpoint_.first + fixedlength*sin(fixedangle),
                      startpoint_.second - fixedlength*cos(fixedangle)};

}
void Flipper::Enable()
{  
  endpoint = endpoint_enabled;
}

void Flipper::Disable()
{
  endpoint = endpoint_disabled;
}
