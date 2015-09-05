#ifndef HW3_LIGHTDATA_H
#define HW3_LIGHTDATA_H


#import "LightAttenuationData.h"

struct LightData {
    float color[3];
    LightAttenuationData attenuation;
};


#endif //HW3_LIGHTDATA_H
