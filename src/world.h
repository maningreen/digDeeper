#ifndef world_h
#define world_h

#include <raylib.h>
#include "include.h"

#define blockLength 50

#define blockCount 3

#define airBias .9

enum blockCodes {
  airCode,
  rockCode,
  mossCode,
  debugCode,
};
#define airColour (Colour){0, 0, 0, 0}
#define rockColour (Colour){176, 95, 64, 255} //#B15F40
#define mossColour (Colour){37, 167, 32, 255} //#25bb20
#define debugColour (Colour){255, 0, 127, 255}//#ff007f

#define colArr (Colour[]){airColour, rockColour, mossColour, debugColour}

typedef struct {
  void* world;
  Vector2 worldDimensions;
} stdWorldArgs;

void initWorld(stdWorldArgs args);

void drawWorld(stdWorldArgs args);

void* initWorldT(void* args);

Rectangle getBlockRect(Vector2 position);

//returns 1 if there is no block for the given index
int drawBlock(unsigned int blockCode, Vector2 position);
//returns 1 if there's no block for that index
int drawBlockV(unsigned int blockCode, Vector2 position);

Vector2 getClosestBlockToPosition(void* world, Vector2 worldDimensions, Vector2 position);

Vector2 getBlockPosition(Vector2 index);

Vector2 getFirstAirBlock(stdWorldArgs args);

#endif
