#pragma once


#include <vector>
#include <string>
#include "glm/glm.hpp"

class Object;
class Camera;
class Light;

class Scene {
public:
    Scene()
        : camera(nullptr) {
    }

    unsigned width;
    unsigned height;
    unsigned maxDepth;
    std::string outputFile;
    std::vector<glm::vec3> verticies;
    std::vector<Object*> objects;
    std::vector<Light*> lights;
    double attenuation[3];
    Camera* camera;
};
