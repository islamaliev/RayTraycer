#include <vector>
#include <iostream>
#include "RayTracer.h"
#include "Image.h"
#include "Scene.h"
#include "Intersection.h"
#include "Object.h"
#include "Camera.h"
#include "Ray.h"

int totalIntersections = 0;
int totalIntersectionChecks = 0;

Image* RayTracer::raytrace(Camera* camera, Scene* scene, int width, int height) {
    w = width;
    h = height;
    halfW = w * 0.5f;
    halfH = h * 0.5f;
    tanHalfFOVX = tanf((float) (camera->fovx * M_PI / 360.f));
    tanHalfFOVY = tanf((float) (camera->fovy * M_PI / 360.f));
    Image* image = new Image(width, height);
    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            Ray* ray = getRayThoughPixel(camera, x + 0.5f, y + 0.5f);
            Intersection* intersection = getIntersection(ray, scene);
            unsigned color = findColor(intersection);
            if (intersection->dist > 0) {
                color = 0xFF0000;
            } else {
                color = 0;
            }

            pushColor(image, color, x, y);
        }
    }
    std::cout << "total intersections: " << totalIntersections << std::endl;
    std::cout << "total intersection checks: " << totalIntersectionChecks << std::endl;
    return image;
}

Ray* RayTracer::getRayThoughPixel(Camera* camera, float x, float y) {
    /*const float smallerDim = ((w < h) ? w : h);
    float zoom = 1;
    const double largeZoom  = zoom * smallerDim;
    vec3 direction(0.0, 0.0, -1.0);
    direction.x = (float) ((x - halfW) / largeZoom);
    direction.y = (float) ((halfH - y) / largeZoom);*/

    const float U = (x - halfW) / halfW;
    const float V = (halfH - y) / halfH;
    float alpha = tanHalfFOVX * U;
    float beta = tanHalfFOVY * V;

    Ray* ray = new Ray();
    ray->pos = camera->pos;
    vec3 rayDir = alpha * camera->right + beta * camera->up - camera->forward;
    vec3 rayDirNorm = glm::normalize(rayDir);
    ray->dir = rayDirNorm;
//    ray->dir = direction;
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
    return 0;
}

float RayTracer::intersect(Ray* ray, Object* object) {
    return object->intersect(ray);
}

void RayTracer::pushColor(Image* image, unsigned int color, unsigned int x, unsigned int y) {
    const unsigned int i = y * 3 * h + x * 3;
    image->data[i + 0] = (unsigned char) (color & 0xFF);
    image->data[i + 1] = (unsigned char) (color >> 8 & 0xFF);
    image->data[i + 2] = (unsigned char) (color >> 16 & 0xFF);
}
