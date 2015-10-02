#pragma once


#include "ObjectData.h"

struct TriangleData : public ObjectData {
    TriangleData(float inds[3]) {
        std::copy(inds, inds + 3, indecies);
    }

    unsigned indecies[3];
    bool hasPerVertexNormal;
};
