#include "world.h"
#include "include.h"
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

void initWorld(stdWorldArgs args) {
  unsigned int (*worldArr)[(int)args.worldDimensions.x] = args.world;
  for(unsigned int i = 0; i < args.worldDimensions.x; i++)
    for(unsigned int j = 0; j < args.worldDimensions.y; j++) {
      if(j == 0 || i == 0 || j + 1 == args.worldDimensions.y || i + 1 == args.worldDimensions.x) {
        worldArr[i][j] = stoneCode;
        continue;
      }
      worldArr[i][j] = (((float)rand() / (float)RAND_MAX) / .75f) > airBias ? (rand() % (blockCount - 1)) + 1 : airCode;
    }
}

int drawBlockV(unsigned int blockCode, Vector2 position) {
  DrawRectangleV(position, (Vector2){blockLength, blockLength}, colArr[blockCode]);
  return 0;
}

void drawWorld(stdWorldArgs args) {
  Vector2 screenDimensions = {GetScreenWidth() + args.camera.target.y - args.camera.offset.y, GetScreenHeight() - args.camera.target.x + args.camera.offset.x};
  unsigned int (*worldArr)[(int)args.worldDimensions.x] = args.world;
  for(unsigned short i = 0; i < args.worldDimensions.x; i++) {
    for(unsigned short j = 0; j < args.worldDimensions.y; j++) {
      Vector2 blockPos = {i * blockLength, j * blockLength};
      if(blockPos.y > screenDimensions.x || -blockPos.x > screenDimensions.y) continue;
      drawBlockV(worldArr[i][j], blockPos);
    }
  }
}

void* initWorldT(void* args) {
  return 0;
}

void* drawWorldT(void* args) {
  drawWorld(*((stdWorldArgs*)args));
  return 0;
}

Rectangle getBlockRect(Vector2 position) {
  return (Rectangle){position.x, position.y, blockLength};
}


int drawBlock(unsigned int blockCode, Vector2 position) {
  return drawBlockV(blockCode, Vector2Scale(position, blockLength));
}

Vector2 getBlockPosition(Vector2 index) {
  return Vector2Scale(index, blockLength);
}

Vector2 getClosestBlockToPosition(void* world, Vector2 worldDimensions, Vector2 position) {
  Vector2 positionInArr = Vector2Scale(position, 1.0f / blockLength); //this gives us the approximate position in the array
  Vector2 floorP = {floorf(positionInArr.x), floorf(positionInArr.y)};
  Vector2 offsetFromArray = Vector2Subtract(positionInArr, floorP);
  return Vector2Add(floorP, (Vector2){floorf(offsetFromArray.x * offsetFromArray.x), floorf(offsetFromArray.y * offsetFromArray.y)});
}

Vector2 getFirstAirBlock(stdWorldArgs args) {
  unsigned int (*worldArr)[(int)args.worldDimensions.x] = args.world;
  for(int i = 0; i < args.worldDimensions.x; i++)
    for(int j = 0; j < args.worldDimensions.y; j++) {
      if(worldArr[i][j] != airCode)
        continue;
      return (Vector2){i, j};
    }
  return Vector2Zero();
}
