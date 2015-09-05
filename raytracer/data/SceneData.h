#ifndef HW3_SCENEDATA_H
#define HW3_SCENEDATA_H


#include <string>
#import "CameraData.h"

struct SceneData {
    int width;
    int height;
    int maxDepth;
    std::string outputFile;

    CameraData camera;

    int maxVerticies;
    int maxVerNorms;

};


#endif //HW3_SCENEDATA_H
