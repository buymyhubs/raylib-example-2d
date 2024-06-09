#include "lib/local_lib.h"
#include "lib/objects.h"
#include "raylib.h"

game_player player = game_player(150,150);

void update_player(float deltaTime) {
    if (IsKeyDown(KEY_D)) {
        player.set_player_x(player.get_x() + player.get_speed()*deltaTime);
    }
    if (IsKeyDown(KEY_A)) {
        player.set_player_x(player.get_x() - player.get_speed()*deltaTime);
    }
    if (IsKeyDown(KEY_W)) {
        player.set_player_y(player.get_y() - player.get_speed()*deltaTime);
    }
    if (IsKeyDown(KEY_S)) {
        player.set_player_y(player.get_y() + player.get_speed()*deltaTime);
    }
}

void draw_player() {
    player.draw();
}