#ifndef circle_h
#define circle_h

#include <raylib.h>
#include "include.h"

struct circle {
  Vector2 position;;
  float radius;
  Colour colour;
};
typedef struct circle Circle;

void drawCircle(Circle c);

#endif
