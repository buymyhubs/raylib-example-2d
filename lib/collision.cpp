
#include <vector>
#include <_xlocale.h>

#include "objects.h"
#include "raylib.h"
#include "scene_constructor.h"

using std::vector;

collision_response check_all_collision(Rectangle check_rectangle, vector<Rectangle> solids, int direction, bool x_axis) {
    bool can_move = true;
    int closest_location = 0;
    for (int i = 0; i < solid_count; i++) {
        if (CheckCollisionRecs(check_rectangle, solids[i])) {
           can_move = false;

            if (direction > 0) {
                closest_location = x_axis ? solids[i].x - check_rectangle.width : solids[i].y - check_rectangle.height;
            } else {
                closest_location = x_axis ? solids[i].x + solids[i].width : solids[i].y + solids[i].height;
            }
        };
    }

    // check against scene collision
    vector<vector<float>> check_points = { { check_rectangle.x, check_rectangle.y }, {check_rectangle.x+check_rectangle.width, check_rectangle.y}, {check_rectangle.x, check_rectangle.y+check_rectangle.height}, {check_rectangle.x+check_rectangle.width, check_rectangle.y+check_rectangle.height} };
    for (int i = 0; i < 4; i++) {
        vector<int> equivalent_collision_point = {static_cast<int>(check_points[i][0]/8), static_cast<int>(check_points[i][1]/8)};
        int collision_line_length = scene.get_collision_line_length();
        vector<bool> scene_collision = scene.get_scene_collision();
        int collision_check_index = equivalent_collision_point[1] * scene.get_collision_line_length() + equivalent_collision_point[0];

        if (scene.get_scene_collision()[collision_check_index]) {
            can_move = false;
            if (!x_axis) {
                // map index back to nearest pixel
                if (direction > 0) {
                    closest_location = (equivalent_collision_point[1] * 8) - check_rectangle.height;
                } else {
                    closest_location = (equivalent_collision_point[1] * 8) + check_rectangle.height;
                }
            } else {
                if (direction > 0) {
                    closest_location = (equivalent_collision_point[0] * 8) - check_rectangle.width;
                } else {
                    closest_location = (equivalent_collision_point[0] * 8) + check_rectangle.width;
                }
            }
        }
    }


    return {can_move, closest_location};



}
