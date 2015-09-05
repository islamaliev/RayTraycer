#pragma once

class Image;
class Camera;
class Scene;
class Ray;
class Intersection;
class Object;

class RayTracer {
public:
    Image* raytrace(Camera* camera, Scene* scene, int width, int height);

private:
    Ray* getRayThoughPixel(Camera* camera, float x, float y);

    Intersection* getIntersection(Ray* ray, Scene* scene);

    unsigned findColor(Intersection* intersection);

    float intersect(Ray* ray, Object* object);

    void pushColor(Image* image, unsigned int color, unsigned int x, unsigned int y);

    int w;
    int h;
    float halfW;
    float halfH;
    float tanHalfFOVX;
    float tanHalfFOVY;

};
