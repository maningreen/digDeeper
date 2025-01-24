#include "player.h"
#include "world.h"
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

#define playerStepCount 10

Vector2 getPlayerInputFromKeys(int l, int r, int u, int d) {
  Vector2 out;
  out.y = IsKeyDown(d) - IsKeyDown(u);
  out.x = IsKeyDown(r) - IsKeyDown(l);
  return Vector2LengthSqr(out) == 1 ? out : Vector2Normalize(out); //cmp is faster than an inverse sqrt
}

void managePlayerInput(Player* plr, float delta) {
  Vector2 input = Vector2Scale(getPlayerInputFromKeys(leftInputKey, rightInputKey, upInputKey, downInputKey), playerSpeed * delta);
  plr->velocity = Vector2Add(input, plr->velocity);
}

void playerApplyVelocity(Player* plr) {
  plr->position = Vector2Add(plr->position, plr->velocity);
}

void managePlayerMotion(Player* plr, void* world, Vector2 worldDimensions) {
  unsigned int (*worldArr)[(int)worldDimensions.x] = world;
  Player stepPlayer = *plr; // i'm stuck! /j
  Vector2 vel = {plr->velocity.x / playerStepCount, plr->velocity.y / playerStepCount};
  Vector2 prePos = stepPlayer.position;
  for(unsigned short i = 0; i < playerStepCount; i++) {
    if(plr->velocity.x != 0) {
      stepPlayer.position = Vector2Add((Vector2){vel.x, 0}, stepPlayer.position);
      stepPlayer.velocity = getClosestBlockToPosition(world, worldDimensions, stepPlayer.position); //this is the most fucked up shit
      if(worldArr[(int)stepPlayer.velocity.x][(int)stepPlayer.velocity.y] == airCode)
        goto cont;
      Vector2 closestPosition = getBlockPosition(stepPlayer.velocity);
      if(CheckCollisionCircleRec(stepPlayer.position, 1, (Rectangle){closestPosition.x, closestPosition.y, blockLength, blockLength})) {
        stepPlayer.position = prePos;
        plr->velocity.x = 0;
      }
    }
  cont:
    prePos = stepPlayer.position;
    if(plr->velocity.y != 0) {
      stepPlayer.position = Vector2Add((Vector2){0, vel.y}, stepPlayer.position);
      stepPlayer.velocity = getClosestBlockToPosition(world, worldDimensions, stepPlayer.position); //this is the most fucked up shit
      if(worldArr[(int)stepPlayer.velocity.x][(int)stepPlayer.velocity.y] == airCode)
        continue;
      Vector2 closestPosition = getBlockPosition(stepPlayer.velocity);
      if(CheckCollisionCircleRec(stepPlayer.position, 1, (Rectangle){closestPosition.x, closestPosition.y, blockLength, blockLength})) {
        stepPlayer.position = prePos;
        plr->velocity.y = 0;
      }
    }
  }
  plr->position = stepPlayer.position;
}

void managePlayer(Player* plr, void* world, Vector2 worldDimensions, float delta) {
  managePlayerMotion(plr, world, worldDimensions);
  Vector2 blockI = getClosestBlockToPosition(world, worldDimensions, plr->position);
  Vector2 blockP = getBlockPosition(blockI);
  drawBlock(debugCode, blockI);
}
