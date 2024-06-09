#include "lib/local_lib.h"
#include "lib/objects.h"
#include "raylib.h"

object tile_test = object(
    100.0f,
    100.0f,
    true,
    false,
    "",
    16,
    16,
    true,
    false
);

void draw_tiles() {
    tile_test.draw();
}