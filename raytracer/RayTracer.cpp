#include "RayTracer.h"
#include "Image.h"
#include "Scene.h"
#include "Intersection.h"
#include "Object.h"
#include "Camera.h"
#include "ProgressReporter.h"
#include "IntersectionDetector.h"
#include "ColorCalculator.h"

void RayTracer::raytraceArea(unsigned index, unsigned count, Scene* scene, Image* image) const {
    unsigned x, y;
    for (unsigned i = index; i < count; i++) {
        y = i / w;
        x = i - y * w;
        Ray* ray = getRayThoughPixel(scene->camera, x + 0.5f, y + 0.5f);
        Intersection* intersection = intersectionDetector->getIntersection(ray);
        unsigned color = colorCalculator->calculate(intersection);
        pushColor(image, color, x, y);
        progressReporter->handleProgress(x, y);
    }
}

Image* RayTracer::raytrace(Scene* scene) {
    init(scene);
    Image* image = new Image(w, h);
    progressReporter = new ProgressReporter(scene->width, scene->height);
    intersectionDetector = new IntersectionDetector(scene);
    colorCalculator = new ColorCalculator(scene, intersectionDetector);

    raytraceArea(0, w * h, scene, image);

    delete progressReporter;
    delete intersectionDetector;
    delete colorCalculator;
    return image;
}

Ray* RayTracer::getRayThoughPixel(const Camera* camera, double x, double y) const {
    const double U = (x - halfW) / halfW;
    const double V = (halfH - y) / halfH;
    double alpha = tanFOVX * U;
    double beta = tanFOVY * V;

    Ray* ray = new Ray();
    ray->pos = vec4(camera->pos, 1);
    vec3 rayDir = alpha * camera->right + beta * camera->up - camera->forward;
    vec3 rayDirNorm = glm::normalize(rayDir);
    ray->dir = vec4(rayDirNorm, 0);
    return ray;
}

void RayTracer::pushColor(Image* image, unsigned int color, unsigned int x, unsigned int y) const {
    const unsigned int i = y * 3 * w + x * 3;
    image->data[i + 0] = (unsigned char) (color & 0xFF);
    image->data[i + 1] = (unsigned char) (color >> 8 & 0xFF);
    image->data[i + 2] = (unsigned char) (color >> 16 & 0xFF);
}

void RayTracer::init(Scene* scene) {
    w = scene->width;
    h = scene->height;
    halfW = w * 0.5f;
    halfH = h * 0.5f;
    double toRadian = M_PI / 360.0;
    tanFOVY = tan(scene->camera->fovy * toRadian);
    tanFOVX = tanFOVY * w / h;
}
