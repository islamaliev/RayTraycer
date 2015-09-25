#pragma once

#include "Ray.h"

class Image;
class Camera;
class Scene;
class Ray;
class Intersection;
class Object;
class ProgressReporter;
class IntersectionDetector;
class ColorCalculator;

class RayTracer {
public:
    RayTracer(){};

    Image* raytrace(Scene* scene);

private:
    void init(Scene* scene);

    void raytraceArea(unsigned index, unsigned count, Scene* scene, Image* image) const;

    Ray* getRayThoughPixel(const Camera* camera, double x, double y) const;

    void pushColor(Image* image, unsigned int color, unsigned int x, unsigned int y) const;

    unsigned w;
    unsigned h;
    double halfW;
    double halfH;
    double tanFOVX;
    double tanFOVY;

    ProgressReporter* progressReporter;
    IntersectionDetector* intersectionDetector;
    ColorCalculator* colorCalculator;
};
