#pragma once


#include <alloca.h>

struct Image {
    Image(int w, int h): width(w), height(h) {
//        data = (unsigned char*) alloca(width * height * 3 * sizeof(unsigned char));
    }
    const int width;
    const int height;
    unsigned char data[640 * 480 * 3];
};
