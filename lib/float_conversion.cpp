#include <string>

std::string float_to_string(const float value) {
    if (value == 0.00f) {
        return "0";
    }
    if (value >= 1000.00f) {
        return std::to_string(value / 1000.00f) + "k";
    }

    try {
        return std::to_string(value);
    } catch (...) {
        return "NaN";
    }
}

