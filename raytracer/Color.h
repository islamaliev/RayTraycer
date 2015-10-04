#pragma once


#include "glm/glm.hpp"

#define BYTE_MASK 0xFF

class Color {
public:
    Color()
        : value(0) {}

    Color(double r, double g, double b)
        : value(r, g, b) {}

    Color(unsigned color) {
        float b = color & BYTE_MASK;
        b /= (float) BYTE_MASK;
        float g = color >> 8 & BYTE_MASK;
        g /= (float) BYTE_MASK;
        float r = color >> 16 & BYTE_MASK;
        r /= (float) BYTE_MASK;
        value = glm::vec3(r, g , b);
    }

    double r() const {
        return value.r;
    }

    double g() const {
        return value.g;
    }

    double b() const {
        return value.b;
    }

    Color operator+(const Color& rhs) const {
        return Color(value + rhs.value);
    }

    Color& operator+=(const Color& rhs) {
        value += rhs.value;
        return *this;
    }

    Color operator-(const Color& rhs) const {
        return Color(value - rhs.value);
    }

    Color& operator-=(const Color& rhs) {
        value -= rhs.value;
        return *this;
    }

    Color operator*(const Color& rhs) const {
        return Color(value * rhs.value);
    }

    Color& operator*=(const Color& rhs) {
        value *= rhs.value;
        return *this;
    }

    Color operator/(const Color& rhs) const {
        return Color(value / rhs.value);
    }

    Color& operator/=(const Color& rhs) {
        value /= rhs.value;
        return *this;
    }

    operator unsigned() const {
        unsigned char r = (unsigned char) (value.r * BYTE_MASK);
        unsigned char g = (unsigned char) (value.g * BYTE_MASK);
        unsigned char b = (unsigned char) (value.b * BYTE_MASK);
        unsigned result(b);
        result |= r << 16;
        result |= g << 8;
        return result;
    }

    void clamp() {
        if (value.r > 1) value.r = 1;
        if (value.g > 1) value.g = 1;
        if (value.b > 1) value.b = 1;
    }

private:
    explicit Color(glm::vec3 vec)
        : value(vec) {}

    glm::vec3 value;

    friend Color operator+(const Color& lhs, const double& scalar);
    friend Color& operator+=(Color& lhs, const double& scalar);
    friend Color operator-(const Color& lhs, const double& scalar);
    friend Color& operator-=(Color& lhs, const double& scalar);
    friend Color operator*(const Color& lhs, const double& scalar);
    friend Color& operator*=(Color& lhs, const double& scalar);
    friend Color operator/(const Color& lhs, const double& scalar);
    friend Color& operator/=(Color& lhs, const double& scalar);
};