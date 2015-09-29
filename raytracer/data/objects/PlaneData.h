#ifndef HW3_PLANEDATA_H
#define HW3_PLANEDATA_H


#import "ObjectData.h"

struct PlaneData : public ObjectData {
    PlaneData(float pos[3], float norm[3], float w, float h, float rotation)
        : w(w)
        , h(h)
        , rotation(rotation) {
        std::copy(pos, pos + 3, position);
        std::copy(norm, norm + 3, normal);
    }

    float w;
    float h;
    float rotation;
    float position[3];
    float normal[3];
};


#endif //HW3_PLANEDATA_H
