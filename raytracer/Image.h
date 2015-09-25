#pragma once


#include <alloca.h>

struct Image {
    Image(int w, int h)
        : width(w)
        , height(h) {
        data = new unsigned char[width * height * 3];
    }

    ~Image() {
        delete[] data;
    }

    const int width;
    const int height;
    unsigned char* data;
};
