#include "circle.h"
#include <raylib.h>

void drawCircle(Circle c) {
  DrawCircleV(c.position, c.radius, c.colour);
}
