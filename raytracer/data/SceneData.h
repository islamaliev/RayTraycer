#ifndef HW3_SCENEDATA_H
#define HW3_SCENEDATA_H


#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "CameraData.h"

class TriangleData;
class SphereData;
class PointLightData;
class DirectionalLightData;

struct SceneData {
    SceneData()
        : maxDepth(5) {
        attenuation[0] = 1;
    }

    unsigned width;
    unsigned height;
    unsigned maxDepth;
    std::string outputFile;

    CameraData camera;

    int maxVerticies;
    int maxVerNorms;
    std::vector<glm::vec3> verticies;
    std::vector<TriangleData*> triangles;
    std::vector<SphereData*> spheres;
    std::vector<PointLightData*> pointLights;
    std::vector<DirectionalLightData*> directionalLights;
    float attenuation[3];
};


#endif //HW3_SCENEDATA_H
