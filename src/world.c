#include "world.h"
#include "include.h"
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>

void initWorld(void* world, Vector2 worldDimensions) {
  unsigned int (*worldArr)[(int)worldDimensions.x] = world;
  for(unsigned int i = 0; i < worldDimensions.x; i++)
    for(unsigned int j = 0; j < worldDimensions.y; j++) {
      worldArr[i][j] = rand() % blockCount;
      printf("%ul\n", worldArr[i][j]);
    }
}


void drawWorld(void* world, Vector2 worldDimensions) {
  unsigned int (*worldArr)[(int)worldDimensions.x] = world;
  for(unsigned int i = 0; i < worldDimensions.x; i++)
    for(unsigned int j = 0; j < worldDimensions.y; j++) {
      Colour col;
      switch(worldArr[i][j]) {
      case rockCode:
        col = rockColour;
        break;
      case airCode:
        col = airColour;
        break;
      }
      Rectangle block = {i * blockLength, j * blockLength, blockLength, blockLength};
      DrawRectangleRec(block, col);
    }
}
