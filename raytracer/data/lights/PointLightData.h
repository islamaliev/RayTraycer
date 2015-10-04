#pragma once


#import "LightData.h"

struct PointLightData : public LightData {
    PointLightData(float pos[3], float col[3], float attn[3])
            : LightData(col) {
        copyf3(pos, position);
        copyf3(attn, attenuation);
    };

    float position[3];
    float attenuation[3];
};
