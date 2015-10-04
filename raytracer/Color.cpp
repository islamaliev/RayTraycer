#include "Color.h"

Color operator+(const Color& lhs, const double& scalar) {
    return Color(lhs.value + scalar);
}

Color& operator+=(Color& lhs, const double& scalar) {
    lhs.value += scalar;
    return lhs;
}

Color operator-(const Color& lhs, const double& scalar) {
    return Color(lhs.value - scalar);
}

Color& operator-=(Color& lhs, const double& scalar) {
    lhs.value -= scalar;
    return lhs;
}

Color operator*(const Color& lhs, const double& scalar) {
    return Color(lhs.value * scalar);
}

Color& operator*=(Color& lhs, const double& scalar) {
    lhs.value *= scalar;
    return lhs;
}

Color operator/(const Color& lhs, const double& scalar) {
    return Color(lhs.value / scalar);
}

Color& operator/=(Color& lhs, const double& scalar) {
    lhs.value /= scalar;
    return lhs;
}