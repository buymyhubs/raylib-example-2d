#include <stdio.h>
#include <string.h>
#include <map>

#include "raylib.h"
#include "local_lib.h"

#include "objects.h"

using namespace std;



void debug_menu() {
    char debug_menu_text[8][64];

    std::string keys_pressed_string = "";

    strcpy(debug_menu_text[0], int_to_string(GetFPS()));
    strcat(debug_menu_text[0], " FPS");

    strcpy(debug_menu_text[1], float_to_string(GetFrameTime()*100));
    strcat(debug_menu_text[1], " delta_time");

    strcpy(debug_menu_text[2], "x: ");
    strcat(debug_menu_text[2], float_to_string(player.get_x()));

    strcpy(debug_menu_text[3], "y: ");
    strcat(debug_menu_text[3], float_to_string(player.get_y()));

    strcpy(debug_menu_text[4], "render_x: ");
    strcat(debug_menu_text[4], int_to_string(player.get_rendered_x()));

    strcpy(debug_menu_text[5], "render_y: ");
    strcat(debug_menu_text[5], int_to_string(player.get_rendered_y()));

    if (IsKeyDown(KEY_W)) {
        keys_pressed_string += " ^";
    }

    if (IsKeyDown(KEY_A)) {
        keys_pressed_string += " <";
    }

    if (IsKeyDown(KEY_S)) {
        keys_pressed_string += " v";
    }

    if (IsKeyDown(KEY_D)) {
        keys_pressed_string += " >";
    }

    if (IsKeyDown(KEY_SPACE)) {
        keys_pressed_string += " JUMP";
    }

    strcpy(debug_menu_text[6], "controls_pressed:");
    strcat(debug_menu_text[6], keys_pressed_string.c_str());

    // DrawText(debug_menu_text[0], 10, 10, 20, WHITE);
    for (int i = 0; i < 7; i++) {
        DrawText(debug_menu_text[i], 4, 4+(i*8), 1, WHITE);
    }


}