#ifndef HW3_TRIANGLEDATA_H
#define HW3_TRIANGLEDATA_H


#import "ObjectData.h"

struct TriangleData : public ObjectData {
    unsigned indecies[3];
    bool hasPerVertexNormal;
};


#endif //HW3_TRIANGLEDATA_H
