#pragma once

#include "Ray.h"
#include "ColorCalculator.h"

class Image;
class Camera;
class Scene;
class Ray;
class Intersection;
class Object;

class RayTracer {
public:
    RayTracer(){};

    Image* raytrace(Scene* scene);

private:
    void init(Scene* scene);

    Ray* getRayThoughPixel(const Camera* camera, float x, float y) const;

    void pushColor(Image* image, unsigned int color, unsigned int x, unsigned int y) const;

    int w;
    int h;
    float halfW;
    float halfH;
    float tanFOVX;
    float tanFOVY;
};
