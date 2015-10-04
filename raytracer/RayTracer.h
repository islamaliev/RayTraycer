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
class Color;

class RayTracer {
public:
    RayTracer(){};

    Image* raytrace(Scene* scene);

private:
    void init();

    void raytraceArea(unsigned index, unsigned count, Image* image) const;

    void runThreads(Image* image) const;

    Ray* getRayThoughPixel(const Camera* camera, double x, double y) const;

    void pushColor(Image* image, const Color& color, unsigned int x, unsigned int y) const;

    unsigned w;
    unsigned h;
    double halfW;
    double halfH;
    double tanFOVX;
    double tanFOVY;

    Scene* scene;
    ProgressReporter* progressReporter;
    IntersectionDetector* intersectionDetector;
    ColorCalculator* colorCalculator;
};
