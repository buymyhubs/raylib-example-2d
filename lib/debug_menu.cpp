#include <stdio.h>
#include <string.h>
#include <map>

#include "raylib.h"
#include "local_lib.h"

#include "objects.h"

using std::string;
using std::vector;


void debug_menu() {
    auto debug_menu_text = vector<string>();


    debug_menu_text.push_back(int_to_string(GetFPS()) + " FPS");
    debug_menu_text.push_back(float_to_string(GetFrameTime() * 100) + " delta_time");
    debug_menu_text.push_back("x: " + float_to_string(player.get_x()));
    debug_menu_text.push_back("y: " + float_to_string(player.get_y()));
    debug_menu_text.push_back("render_x: " + int_to_string(player.get_rendered_x()));
    debug_menu_text.push_back("render_y: " + int_to_string(player.get_rendered_y()));

    string keys_pressed_string;

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

    debug_menu_text.push_back("controls_pressed: " + keys_pressed_string);

    for (int i = 0; i < debug_menu_text.size(); i++) {
        DrawText(debug_menu_text[i].c_str(), 4, 4 + (i * 24), 24, WHITE);
    }
}
