
#include <vector>
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

    float collision_point_index = pixel_location_to_collision_index(normalize(check_rectangle.x/8)*8, normalize(check_rectangle.y/8)*8);
    float left_collision_point_index = pixel_location_to_collision_index(check_rectangle.x, normalize(check_rectangle.y/8)*8);
    float x_right_point = check_rectangle.x+check_rectangle.width;
    float right_collision_point_index = pixel_location_to_collision_index(x_right_point-1, check_rectangle.y);

    Rectangle tile_collider_rectangle = check_rectangle;

    int collision_axis_rounding_correction = 0;

    if (x_axis) {
        if (direction > 0) {
            if (checkable_tiles_collision[collision_point_index+1]) {
                tile_collider_rectangle.x = collision_index_to_pixel_location(collision_point_index+1)[0];
                checkable_solids.push_back(tile_collider_rectangle);
                checkable_solids_count++;
            }
        } else if (direction < 0) {
            if (checkable_tiles_collision[collision_point_index-1]) {
                tile_collider_rectangle.x = collision_index_to_pixel_location(collision_point_index-1)[0];
                checkable_solids.push_back(tile_collider_rectangle);
                checkable_solids_count++;
            }
        }
    } else {
        if (direction > 0) {
            if (checkable_tiles_collision[left_collision_point_index + collision_line_length] || checkable_tiles_collision[right_collision_point_index + collision_line_length]) {
                tile_collider_rectangle.y = collision_index_to_pixel_location(collision_point_index+scene.get_collision_line_length())[1];
                checkable_solids.push_back(tile_collider_rectangle);
                checkable_solids_count++;
            }
        } else if (direction < 0) {
            if (checkable_tiles_collision[collision_point_index - collision_line_length]) {
                tile_collider_rectangle.y = collision_index_to_pixel_location(collision_point_index-scene.get_collision_line_length())[1];
                checkable_solids.push_back(tile_collider_rectangle);
                checkable_solids_count++;
            }
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

