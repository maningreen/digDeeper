#include <raylib.h>
#include <raymath.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "world.h"
#include "player.h"

#define defaultScreenDimensions (Vector2){500 * 16/9, 500 / (16 / 9)}
#define backroundColour BLACK

#define quitKey KEY_Q

#define worldDimensions (Vector2){50, 50}

int main() {
  srand(time(0));
  InitWindow(defaultScreenDimensions.x, defaultScreenDimensions.y, "Dig Deeper");
  SetTargetFPS(60);

  unsigned int world[(int)worldDimensions.x][(int)worldDimensions.y];
  initWorld((void*)world, worldDimensions);

  Player plr = {{0}, {0}, playerRadius, playerColour};

  while(!WindowShouldClose()) {
    float delta = GetFrameTime();
    BeginDrawing();

    ClearBackground(backroundColour);
    drawWorld(world, worldDimensions);

    managePlayerInput(&plr, delta);
    playerApplyVelocity(&plr);

    managePlayer(&plr, world, worldDimensions, delta);
    DrawCircleV(plr.position, plr.radius, plr.col);

    plr.velocity = Vector2Scale(plr.velocity, playerFriction);

    EndDrawing();

    if(IsKeyDown(quitKey))
      break;
  }
  CloseWindow();
  return 0;
}
