#ifndef HW3_SPHEREDATA_H
#define HW3_SPHEREDATA_H


#import "ObjectData.h"

struct SphereData : public ObjectData {
    SphereData(float pos[3], float radius)
        : radius(radius) {
        std::copy(pos, pos + 3, position);
    }

    float position[3];
    float radius;
};


#endif //HW3_SPHEREDATA_H
