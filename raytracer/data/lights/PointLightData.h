#ifndef HW3_POINTLIGHTDATA_H
#define HW3_POINTLIGHTDATA_H


#import "LightData.h"

struct PointLightData : public LightData {
    PointLightData(float pos[3], float col[3])
            : LightData(col) {
        copyf3(pos, position);
    };

    float position[3];
};


#endif //HW3_POINTLIGHTDATA_H
