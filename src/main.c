#include <raylib.h>
#include <raymath.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include "world.h"
#include "player.h"
#include "camera.h"

#define defaultScreenDimensionScalar 700
#define defaultScreenDimensions (Vector2){defaultScreenDimensionScalar * 16/9, defaultScreenDimensionScalar / (16 / 9)}
#define backroundColour BLACK

#define quitKey KEY_Q

#define worldDimensions (Vector2){100, 100}

int main() {
  srand(time(0));
  InitWindow(defaultScreenDimensions.x, defaultScreenDimensions.y, "Dig Deeper");
  SetTargetFPS(60);

  pthread_t tid;

  unsigned int world[(int)worldDimensions.x][(int)worldDimensions.y];
  initWorld((stdWorldArgs){world, worldDimensions});

  Player plr = {Vector2Add(getBlockPosition(getFirstAirBlock((stdWorldArgs){world, worldDimensions})), (Vector2){blockLength / 2, blockLength / 2}), {0}, playerRadius, playerColour};
  Camera2D camera = {{0}, {0}, 0, 1};


  while(!WindowShouldClose()) {
    float delta = GetFrameTime();

    applyCameraSmoothing(&camera, plr.position);
    camera.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

    BeginDrawing();

    BeginMode2D(camera);
    ClearBackground(backroundColour);
    drawWorld((stdWorldArgs){world, worldDimensions}, camera);

    managePlayerInput(&plr, delta);

    managePlayerMovement(&plr, world, worldDimensions);
    DrawCircleV(plr.position, plr.radius, plr.col);

    plr.velocity = Vector2Scale(plr.velocity, playerFriction);


    EndDrawing();

    if(IsKeyDown(quitKey))
      break;
  }
  CloseWindow();
  return 0;
}
