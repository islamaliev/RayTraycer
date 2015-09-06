#ifndef HW3_TRIANGLEDATA_H
#define HW3_TRIANGLEDATA_H


#include "ObjectData.h"

struct TriangleData : public ObjectData {
    TriangleData(unsigned ind1, unsigned ind2, unsigned ind3) {
        indecies[0] = ind1;
        indecies[1] = ind2;
        indecies[2] = ind3;
    }

    unsigned indecies[3];
    bool hasPerVertexNormal;
};


#endif //HW3_TRIANGLEDATA_H
