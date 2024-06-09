#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "local_lib.h"



void debug_menu() {
    char debug_menu_text[8][64];
    strcpy(debug_menu_text[0], int_to_string(GetFPS()));
    strcat(debug_menu_text[0], " FPS");

    strcpy(debug_menu_text[1], float_to_string(GetFrameTime()*100));
    strcat(debug_menu_text[1], " delta_time");


    // DrawText(debug_menu_text[0], 10, 10, 20, WHITE);
    for (int i = 0; i < 2; i++) {
        DrawText(debug_menu_text[i], 10, 4+(i*8), 4, WHITE);
    }
}