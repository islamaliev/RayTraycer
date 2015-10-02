#pragma once


#import "LightData.h"

struct PointLightData : public LightData {
    PointLightData(float pos[3], float col[3])
            : LightData(col) {
        copyf3(pos, position);
    };

    float position[3];
};
