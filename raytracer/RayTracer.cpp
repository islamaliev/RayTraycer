#include <vector>
#include <iostream>
#include "RayTracer.h"
#include "Image.h"
#include "Scene.h"
#include "Intersection.h"
#include "Object.h"
#include "Camera.h"
#include "Triangle.h"

int totalIntersections = 0;
int totalIntersectionChecks = 0;

Image* RayTracer::raytrace(Scene* scene) {
    w = scene->width;
    h = scene->height;
    halfW = w * 0.5f;
    halfH = h * 0.5f;
    float toRadian = (float) (M_PI / 360.f);
    tanFOVX = tanf(scene->camera->fovx * toRadian);
    tanFOVY = tanf(scene->camera->fovy * toRadian);
    Image* image = new Image(w, h);
    for (unsigned x = 0; x < w; x++) {
        for (unsigned y = 0; y < h; y++) {
            Ray* ray = getRayThoughPixel(scene->camera, x + 0.5f, y + 0.5f);
            Intersection* intersection = getIntersection(ray, scene);
            unsigned color = findColor(intersection);
            pushColor(image, color, x, y);
        }
    }
    std::cout << "total intersections: " << totalIntersections << std::endl;
    std::cout << "total intersection checks: " << totalIntersectionChecks << std::endl;
    return image;
}

Ray* RayTracer::getRayThoughPixel(Camera* camera, float x, float y) {
    const float U = (x - halfW) / halfW;
    const float V = (halfH - y) / halfH;
    float alpha = tanFOVX * U;
    float beta = tanFOVY * V;

    Ray* ray = new Ray();
    ray->pos = camera->pos;
    vec3 rayDir = alpha * camera->right + beta * camera->up - camera->forward;
    vec3 rayDirNorm = glm::normalize(rayDir);
    ray->dir = rayDirNorm;
    return ray;
}

Intersection* RayTracer::getIntersection(Ray* ray, Scene* scene) {
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
        if (currentDist > 0)
            totalIntersections++;
    }
    totalIntersectionChecks++;
    return new Intersection(minDist, ray, hitObject);
}

unsigned RayTracer::findColor(Intersection* intersection) {
    if (intersection->dist <= 0) {
        return 0;
    }
    unsigned color = convertToColor(intersection->object->ambient);
    return color;
}

float RayTracer::intersect(Ray* ray, Object* object) {
    return object->intersect(ray);
}

void RayTracer::pushColor(Image* image, unsigned int color, unsigned int x, unsigned int y) {
    const unsigned int i = y * 3 * w + x * 3;
    image->data[i + 0] = (unsigned char) (color & 0xFF);
    image->data[i + 1] = (unsigned char) (color >> 8 & 0xFF);
    image->data[i + 2] = (unsigned char) (color >> 16 & 0xFF);
}

unsigned int RayTracer::convertToColor(float chanels[3]) {
    unsigned char mask = 0xFF;
    unsigned char r = (unsigned char) (chanels[0] * mask);
    unsigned char g = (unsigned char) (chanels[1] * mask);
    unsigned char b = (unsigned char) (chanels[2] * mask);
    unsigned color(b);
    color |= r << 16;
    color |= g << 8;
    return color;
}
