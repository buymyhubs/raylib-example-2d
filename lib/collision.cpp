
#include <vector>
#include <_xlocale.h>
#include <_xlocale.h>

#include "objects.h"
#include "raylib.h"
#include "scene_constructor.h"

using std::vector;


int pixel_location_to_collision_index(int x, int y) {
    return (y/8) * scene.get_collision_line_length() + (x/8);
}

vector<int> collision_index_to_pixel_location(int index) {
    int x = index % scene.get_collision_line_length();
    int y = index / scene.get_collision_line_length();
    return vector<int>{x*8, y*8};
}

collision_response check_all_collision(Rectangle check_rectangle, vector<Rectangle> solids, int direction, bool x_axis) {
    bool can_move = true;
    int closest_location = 0;
    vector<bool> checkable_tiles_collision = scene.get_scene_collision();
    vector<Rectangle> checkable_solids = solids;
    int checkable_solids_count = solid_count;
    int collision_line_length = scene.get_collision_line_length();
    vector<float> check_middle = vector<float>{check_rectangle.x + check_rectangle.width/2, check_rectangle.y + check_rectangle.height/2};

    int checkable_tile_middle_index;
    vector<int> checkable_tile_indexes = vector<int>();

    if (x_axis) {
        if (direction > 0) {
            checkable_tile_middle_index = pixel_location_to_collision_index(check_middle[0]+check_rectangle.width, check_middle[1]);
        } else {
            checkable_tile_middle_index = pixel_location_to_collision_index(check_middle[0]-check_rectangle.width, check_middle[1]);
        }
        checkable_tile_indexes.push_back(checkable_tile_middle_index);
        checkable_tile_indexes.push_back(checkable_tile_middle_index+collision_line_length);
        checkable_tile_indexes.push_back(checkable_tile_middle_index-collision_line_length);
    } else {
        if (direction > 0) {
            checkable_tile_middle_index = pixel_location_to_collision_index(check_middle[0], check_middle[1]+check_rectangle.height);
        } else {
            checkable_tile_middle_index = pixel_location_to_collision_index(check_middle[0], check_middle[1]-check_rectangle.height);
        }
        checkable_tile_indexes.push_back(checkable_tile_middle_index);
        checkable_tile_indexes.push_back(checkable_tile_middle_index+1);
        checkable_tile_indexes.push_back(checkable_tile_middle_index-1);
    }

    for (int i = 0; i < checkable_tile_indexes.size(); i++) {
        if (checkable_tiles_collision[checkable_tile_indexes[i]]) {
            vector<int> pixel_location = collision_index_to_pixel_location(checkable_tile_indexes[i]);
            Rectangle checkable_tile = {(float)pixel_location[0], (float)pixel_location[1], 8, 8};
            checkable_solids.push_back(checkable_tile);
            checkable_solids_count++;
        }
    }




    for (int i = 0; i < checkable_solids_count; i++) {
        DrawRectangleRec(checkable_solids[i], RED);
        if (CheckCollisionRecs(check_rectangle, checkable_solids[i])) {
           can_move = false;

            if (direction > 0) {
                closest_location = x_axis ? checkable_solids[i].x - check_rectangle.width : checkable_solids[i].y - check_rectangle.height;
            } else {
                closest_location = x_axis ? checkable_solids[i].x + checkable_solids[i].width : checkable_solids[i].y + checkable_solids[i].height;
            }
        };
    }

    return {can_move, closest_location};
}

