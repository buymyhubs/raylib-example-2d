#ifndef LOCAL_LIB_H
#define LOCAL_LIB_H
#include <stdbool.h>

char * float_to_string(float value);

char * int_to_string(int value);

void debug_menu();

void update_player(float deltaTime);

void draw_player();
void draw_tiles();

#endif //LOCAL_LIB_H
