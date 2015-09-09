#ifndef HW3_LIGHTDATA_H
#define HW3_LIGHTDATA_H


#include "LightAttenuationData.h"

class LightData {
public:
    LightData(float col[3]) {
        copyf3(col, color);
    }

    float color[3];
    LightAttenuationData attenuation;

protected:
    void copyf3(float src[3], float dest[3]);
};


#endif //HW3_LIGHTDATA_H
