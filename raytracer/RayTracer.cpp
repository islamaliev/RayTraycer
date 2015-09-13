#include <vector>
#include <iostream>
#include "RayTracer.h"
#include "Image.h"
#include "Scene.h"
#include "Intersection.h"
#include "Object.h"
#include "Camera.h"
#include "Triangle.h"
#include "ProgressReporter.h"

Image* RayTracer::raytrace(Scene* scene) {
    w = scene->width;
    h = scene->height;
    halfW = w * 0.5f;
    halfH = h * 0.5f;
    float toRadian = (float) (M_PI / 360.f);
    tanFOVY = tanf(scene->camera->fovy * toRadian);
    tanFOVX = tanFOVY * w / h;
    Image* image = new Image(w, h);
    ColorCalculator colorCalculator(scene);
    ProgressReporter progressReporter(scene->width, scene->height);
    for (unsigned y = 0; y < h; y++) {
        for (unsigned x = 0; x < w; x++) {
            Ray* ray = getRayThoughPixel(scene->camera, x + 0.5f, y + 0.5f);
            Intersection* intersection = getIntersection(ray, scene);
            unsigned color = colorCalculator.calculate(intersection);
            pushColor(image, color, x, y);
            progressReporter.handleProgress(x, y);
        }
    }
    return image;
}

Ray* RayTracer::getRayThoughPixel(const Camera* camera, float x, float y) const {
    const float U = (x - halfW) / halfW;
    const float V = (halfH - y) / halfH;
    float alpha = tanFOVX * U;
    float beta = tanFOVY * V;

    Ray* ray = new Ray();
    ray->pos = vec4(camera->pos, 1);
    vec3 rayDir = alpha * camera->right + beta * camera->up - camera->forward;
    vec3 rayDirNorm = glm::normalize(rayDir);
    ray->dir = vec4(rayDirNorm, 0);
    return ray;
}

Intersection* RayTracer::getIntersection(Ray* ray, Scene* scene) const {
    float minDist = 0;
    float currentDist;
    Object* hitObject = nullptr;
    std::vector<Object*>& objects = scene->objects;
    for (auto it = objects.begin(); it != objects.end(); it++) {
        currentDist = intersect(ray, *it);
        if (currentDist > 0 && (currentDist < minDist || minDist == 0)) {
            minDist = currentDist;
            hitObject = *it;
        }
    }
    return new Intersection(minDist, ray, hitObject);
}

float RayTracer::intersect(const Ray* ray, const Object* object) const {
    return object->intersect(ray);
}

void RayTracer::pushColor(Image* image, unsigned int color, unsigned int x, unsigned int y) const {
    const unsigned int i = y * 3 * w + x * 3;
    image->data[i + 0] = (unsigned char) (color & 0xFF);
    image->data[i + 1] = (unsigned char) (color >> 8 & 0xFF);
    image->data[i + 2] = (unsigned char) (color >> 16 & 0xFF);
}
