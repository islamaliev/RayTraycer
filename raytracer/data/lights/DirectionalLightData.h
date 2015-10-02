#pragma once


#include "LightData.h"

struct DirectionalLightData : public LightData {
public:
    DirectionalLightData(float dir[3], float col[3])
            : LightData(col) {
        copyf3(dir, direction);
    }

    float direction[3];
};
