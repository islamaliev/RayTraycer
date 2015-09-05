#ifndef HW3_SCENEDATA_H
#define HW3_SCENEDATA_H


#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "CameraData.h"

struct SceneData {
    int width;
    int height;
    int maxDepth;
    std::string outputFile;

    CameraData camera;

    int maxVerticies;
    int maxVerNorms;
    std::vector<glm::vec3> verticies;
    std::vector<unsigned> indecies;
};


#endif //HW3_SCENEDATA_H
