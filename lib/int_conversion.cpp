#include <stdio.h>

char * int_to_string(int value) {
    static char buffer[32];
    sprintf(buffer, "%d", value);
    return buffer;
}