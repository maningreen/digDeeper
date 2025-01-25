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

void managePlayerMovement(Player* plr, void* world, Vector2 worldDimensions) {
  unsigned int (*worldArr)[(int)worldDimensions.x] = world;
  Player stepPlayer = *plr; // i'm stuck! /j
  stepPlayer.col.r = 0;
  Vector2 vel = {plr->velocity.x / playerStepCount, plr->velocity.y / playerStepCount};
  for(stepPlayer.col.a = 0; stepPlayer.col.a < playerStepCount; stepPlayer.col.a++) {
    if(!(stepPlayer.col.r & 1)) {
      float prePos = stepPlayer.position.x;
      stepPlayer.position.x += vel.x;
      stepPlayer.velocity = getClosestBlockToPosition(world, worldDimensions, stepPlayer.position); //this is the most fucked up shit
      for(int i = -1; i < 2; i++) {
        if(stepPlayer.velocity.x + i < 0 || stepPlayer.velocity.x + i >= worldDimensions.x)
          continue;
        for(int j = -1; j < 2; j++) {
          if(worldArr[i + (int)stepPlayer.velocity.x][j + (int)stepPlayer.velocity.y] == airCode || stepPlayer.velocity.y + j < 0 || stepPlayer.velocity.y + j >= worldDimensions.y)
            continue;
          Vector2 itemPosition = getBlockPosition(Vector2Add(stepPlayer.velocity, (Vector2){i, j}));
          if(CheckCollisionCircleRec(stepPlayer.position, stepPlayer.radius, (Rectangle){itemPosition.x, itemPosition.y, blockLength, blockLength})) {
            stepPlayer.position.x = prePos;
            stepPlayer.col.r |= 1;
            plr->velocity.x = 0;
          }
        }
      }
    }
  cont:
    if(!(stepPlayer.col.r & 2)) {
      float prePos = stepPlayer.position.y;
      stepPlayer.position.y += vel.y;
      stepPlayer.velocity = getClosestBlockToPosition(world, worldDimensions, stepPlayer.position);
      for(int i = -1; i < 2; i++) {
        if(stepPlayer.velocity.x + i < 0 || stepPlayer.velocity.x + i >= worldDimensions.x)
          continue;
        for(int j = -1; j < 2; j++) {
          if(worldArr[i + (int)stepPlayer.velocity.x][j + (int)stepPlayer.velocity.y] == airCode || stepPlayer.velocity.y + j < 0 || stepPlayer.velocity.y + j >= worldDimensions.y)
            continue;
          Vector2 itemPosition = getBlockPosition(Vector2Add(stepPlayer.velocity, (Vector2){i, j}));
          if(CheckCollisionCircleRec(stepPlayer.position, stepPlayer.radius, (Rectangle){itemPosition.x, itemPosition.y, blockLength, blockLength})) {
            stepPlayer.position.y = prePos;
            stepPlayer.col.r |= 2;
            plr->velocity.y = 0;
          }
        }
      }
    }
  }
  plr->position = stepPlayer.position;
}

void managePlayer(Player* plr, void* world, Vector2 worldDimensions, float delta) {
  managePlayerMovement(plr, world, worldDimensions);
}
