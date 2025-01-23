#ifndef world_h
#define world_h

#include <raylib.h>

#define blockLength 100

#define blockCount 2

#define airCode 0
#define airColour (Colour){0};
#define rockCode 1
#define rockColour (Colour){176, 95, 64, 255} //#B15F40

void initWorld(void* world, Vector2 worldDimensions);

void drawWorld(void* world, Vector2 worldDimensions);

#endif
