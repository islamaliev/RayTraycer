#pragma once


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
