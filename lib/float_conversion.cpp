#include <stdio.h>

char * float_to_string(float value) {
    static char buffer[32];
    sprintf(buffer, "%f", value);
    return buffer;
}
