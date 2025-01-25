#include "camera.h"
#include <raylib.h>
#include <raymath.h>

void applyCameraSmoothing(Camera2D* cam, Vector2 target) {
  cam->target = Vector2Lerp(cam->target, target, cameraSmoothingConst);
}
