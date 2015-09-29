#ifndef HW3_BOXDATA_H
#define HW3_BOXDATA_H


#import "ObjectData.h"

struct BoxData : public ObjectData {
    BoxData(float pos[3], float size)
        : size(size) {
        std::copy(pos, pos + 3, position);
    }

    float position[3];
    float size;
};


#endif //HW3_BOXDATA_H
