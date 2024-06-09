#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "local_lib.h"
#include "objects.h"



void debug_menu() {
    char debug_menu_text[8][64];
    strcpy(debug_menu_text[0], int_to_string(GetFPS()));
    strcat(debug_menu_text[0], " FPS");

    strcpy(debug_menu_text[1], float_to_string(GetFrameTime()*100));
    strcat(debug_menu_text[1], " delta_time");

    strcpy(debug_menu_text[2], int_to_string(player.get_x()));
    strcat(debug_menu_text[2], " player_x");

    strcpy(debug_menu_text[3], int_to_string(player.get_y()));
    strcat(debug_menu_text[3], " player_y");

    strcpy(debug_menu_text[4], int_to_string(player.get_real_x()));
    strcat(debug_menu_text[4], " player_real_x");

    strcpy(debug_menu_text[5], int_to_string(player.get_real_y()));
    strcat(debug_menu_text[5], " player_real_y");


    // DrawText(debug_menu_text[0], 10, 10, 20, WHITE);
    for (int i = 0; i < 6; i++) {
        DrawText(debug_menu_text[i], 10, 4+(i*8), 4, WHITE);
    }
}