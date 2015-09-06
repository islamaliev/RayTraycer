#pragma once


#include <vector>

class Object;
class Camera;

class Scene {
public:
    std::vector<Object*> objects;
    Camera* camera;
};
