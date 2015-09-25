#pragma once


#include <vector>
#include <string>

class Object;
class Camera;
class Light;

class Scene {
public:
    unsigned width;
    unsigned height;
    unsigned maxDepth;
    std::string outputFile;
    std::vector<Object*> objects;
    std::vector<Light*> lights;
    double attenuation[3];
    Camera* camera;
};
