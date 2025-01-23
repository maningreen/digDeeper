#include <raylib.h>
#include <raymath.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "world.h"

#define defaultScreenDimensions (Vector2){1000 * 16/9, 1000 / (16 / 9)}
#define backroundColour BLACK

#define quitKey KEY_ESCAPE

int main() {
  srand(time(0));
  InitWindow(defaultScreenDimensions.x, defaultScreenDimensions.y, "Dig Deeper");
  SetTargetFPS(60);
  unsigned int test[3][3];
  initWorld((void*)test, Vector2Scale(Vector2One(), 3));
  while(!WindowShouldClose()) {
    BeginDrawing();
    drawWorld((void*)test, Vector2Scale(Vector2One(), 3));
    EndDrawing();

    if(IsKeyDown(quitKey))
      break;
  }
  CloseWindow();
  return 0;
}
