#include <stdio.h>
#include <string>

std::string int_to_string(int value) {
    if (value == 0) {
        return "0";
    }
    if (value >= 1000) {
        return std::to_string(value / 1000.00f) + "k";
    }

    try {
        return std::to_string(value);
    }
    catch (...) {
        return "NaN";
    }
}
