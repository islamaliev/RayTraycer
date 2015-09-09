#include "LightData.h"
#import <algorithm>

void LightData::copyf3(float src[3], float dest[3]){
    std::copy(src, src + 3, dest);
}
