#pragma once


#include <vector>

class Object;
class Camera;
class Light;

class Scene {
public:
    unsigned width;
    unsigned height;
    std::vector<Object*> objects;
    std::vector<Light*> lights;
    Camera* camera;
};
