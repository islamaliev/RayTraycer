#pragma once


#import "LightData.h"

struct AmbientLightData : public LightData {
    AmbientLightData(float col[3])
            : LightData(col) {
    }
};
