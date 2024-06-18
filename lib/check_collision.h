#ifndef CHECK_COLLISION_H
#define CHECK_COLLISION_H
#include "raylib.h"

struct collision_response {
    bool can_move;
    int closest_location;
};


collision_response check_all_collision(Rectangle, const std::vector<Rectangle> &, int, bool);

#endif //CHECK_COLLISION_H
