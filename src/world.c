#include "world.h"
#include "include.h"
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

void initWorld(void* world, Vector2 worldDimensions) {
  unsigned int (*worldArr)[(int)worldDimensions.x] = world;
  for(unsigned int i = 0; i < worldDimensions.x; i++)
    for(unsigned int j = 0; j < worldDimensions.y; j++)
      worldArr[i][j] = rand() % blockCount;
}

int drawBlockV(unsigned int blockCode, Vector2 position) {
  DrawRectangleV(position, (Vector2){blockLength, blockLength}, colArr[blockCode]);
  return 0;
}

void drawWorld(void* world, Vector2 worldDimensions) {
  Vector2 screenDimensions = {GetScreenWidth(), GetScreenHeight()};
  unsigned int (*worldArr)[(int)worldDimensions.x] = world;
  Vector2 blockPos = {0, 0};
  for(unsigned int i = 0; i < worldDimensions.x; i++) {
    for(unsigned int j = 0; j < worldDimensions.y; j++) {
      if(i * blockLength > screenDimensions.x || j * blockLength > screenDimensions.y) break;
      drawBlockV(worldArr[i][j], blockPos);
    end:
      blockPos.y += blockLength;
    }
    blockPos.y = 0;
    blockPos.x += blockLength;
  }
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
