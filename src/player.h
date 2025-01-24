#ifndef player_h
#define player_h

#include <raylib.h>
#include "include.h"

#define playerSpeed 25
#define playerRadius 10
#define playerColour WHITE

#define playerFriction .9

#define upInputKey KEY_W
#define downInputKey KEY_S
#define leftInputKey KEY_A
#define rightInputKey KEY_D

struct player {
  Vector2 position;
  Vector2 velocity;
  float radius;
  Colour col;
};
typedef struct player Player;

Vector2 getPlayerInputFromKeys(int l, int r, int u, int d);

void managePlayerInput(Player* plr, float delta);

void playerApplyVelocity(Player* plr);

void managePlayer(Player* plr, void* world, Vector2 worldDimensions, float delta);

#endif
