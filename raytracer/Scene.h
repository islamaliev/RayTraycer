#pragma once


#include <vector>

class Object;
class Camera;

class Scene {
public:
    unsigned width;
    unsigned height;
    std::vector<Object*> objects;
    Camera* camera;
};
