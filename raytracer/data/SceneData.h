#pragma once


#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "CameraData.h"

class TriangleData;
class SphereData;
class PlaneData;
class BoxData;
class PointLightData;
class DirectionalLightData;

struct SceneData {
    SceneData()
        : maxDepth(5) {
    }

    unsigned width;
    unsigned height;
    unsigned maxDepth;
    std::string outputFile;

    CameraData camera;

    std::vector<glm::vec3> verticies;
    std::vector<TriangleData*> triangles;
    std::vector<SphereData*> spheres;
    std::vector<BoxData*> boxes;
    std::vector<PlaneData*> planes;
    std::vector<PointLightData*> pointLights;
    std::vector<DirectionalLightData*> directionalLights;
};
