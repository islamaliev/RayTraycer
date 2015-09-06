#ifndef HW3_TRIANGLEDATA_H
#define HW3_TRIANGLEDATA_H


#include "ObjectData.h"

struct TriangleData : public ObjectData {
    TriangleData(float inds[3]) {
        std::copy(inds, inds + 3, indecies);
    }

    unsigned indecies[3];
    bool hasPerVertexNormal;
};


#endif //HW3_TRIANGLEDATA_H
