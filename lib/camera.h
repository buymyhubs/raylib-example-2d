#ifndef CAMERA_H
#define CAMERA_H

#include <raylib.h>

#include "objects.h"

class game_camera {
private:
    Camera2D camera_inner{};

public:
    game_camera() {
        camera_inner = Camera2D{
            {0.0f, 0.0f},
            {0.0f, 0.0f},
            0.0f,
            1.0f
        };
    }

    void update_camera_x(const int x, float deltaTime) {
        if (x != camera_inner.target.x) {
            float diff = round(x) - camera_inner.target.x;
            camera_inner.target.x = camera_inner.target.x + (diff * 0.08f);
        }
    }

    void update_camera_y(const int y, float deltaTime) {
        if (y != camera_inner.target.y) {
            float diff = round(y) - camera_inner.target.y;
            camera_inner.target.y = camera_inner.target.y + (diff * 0.08f);
        }
    }

    void update_camera(float deltaTime) {
        update_camera_x(player.get_screen_x_coordinate(), deltaTime);
        update_camera_y(player.get_screen_y_coordinate(), deltaTime);
    }

    Camera2D get_inner_object() {
        return camera_inner;
    }
};

#endif //CAMERA_H
