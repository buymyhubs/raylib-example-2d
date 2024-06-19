#include <string>

std::string int_to_string(const int value) {
    try {
        return std::to_string(value);
    } catch (...) {
        return "NaN";
    }
}
