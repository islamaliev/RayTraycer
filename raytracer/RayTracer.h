#pragma once

#include "Ray.h"

class Image;
class Camera;
class Scene;
class Ray;
class Intersection;
class Object;

class RayTracer {
public:
    RayTracer(){}

    Image* raytrace(Scene* scene);

private:
    Ray* getRayThoughPixel(const Camera* camera, float x, float y) const;

    Intersection* getIntersection(Ray* ray, Scene* scene) const;

    unsigned findColor(Intersection* intersection) const;

    float intersect(const Ray* ray, const Object* object) const;

    void pushColor(Image* image, unsigned int color, unsigned int x, unsigned int y) const;

    unsigned int convertToColor(float chanels[3]) const;

    int w;
    int h;
    float halfW;
    float halfH;
    float tanFOVX;
    float tanFOVY;
};
