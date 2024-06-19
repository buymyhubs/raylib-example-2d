#include <string>

std::string float_to_string(const float value) {
    try {
        return std::to_string(value);
    } catch (...) {
        return "NaN";
    }
}

