#ifndef HW3_SCENEDATA_H
#define HW3_SCENEDATA_H


#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "CameraData.h"
#include "TriangleData.h"
#include "SphereData.h"

struct SceneData {
    unsigned width;
    unsigned height;
    int maxDepth;
    std::string outputFile;

    CameraData camera;

    int maxVerticies;
    int maxVerNorms;
    std::vector<glm::vec3> verticies;
    std::vector<TriangleData*> triangles;
    std::vector<SphereData*> spheres;
};


#endif //HW3_SCENEDATA_H
