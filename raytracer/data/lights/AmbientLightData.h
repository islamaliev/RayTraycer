#ifndef HW3_AMBIENTLIGHTDATA_H
#define HW3_AMBIENTLIGHTDATA_H


#import "LightData.h"

struct AmbientLightData : public LightData {
    AmbientLightData(float col[3])
            : LightData(col) {
    }
};


#endif //HW3_AMBIENTLIGHTDATA_H
