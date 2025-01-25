#ifndef camera_h
#define camera_h

#include <raylib.h>

#define cameraSmoothingConst .1f

void applyCameraSmoothing(Camera2D* cam, Vector2 target);

#endif
