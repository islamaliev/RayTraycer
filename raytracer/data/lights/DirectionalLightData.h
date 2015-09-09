#ifndef HW3_DIRECTIONALLIGHTDATA_H
#define HW3_DIRECTIONALLIGHTDATA_H


#include "LightData.h"

struct DirectionalLightData : public LightData {
public:
    DirectionalLightData(float dir[3], float col[3])
            : LightData(col) {
        copyf3(dir, direction);
    }

    float direction[3];
};


#endif //HW3_DIRECTIONALLIGHTDATA_H
