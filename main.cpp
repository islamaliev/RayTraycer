#define MAINPROGRAM

#include <iostream>
#include "variables.h"
#include "readfile.h"
#include "FreeImage.h"
#include "raytracer/Scene.h"
#include "raytracer/Triangle.h"
#include "raytracer/Camera.h"
#include "raytracer/RayTracer.h"
#include "Image.h"

Scene scene;
Camera camera;

void initializeScene() {
    for (auto it = indecies.begin(); it != indecies.end(); it += 3) {
        Triangle* triangle = new Triangle(&verticies[*it], &verticies[*(it + 1)], &verticies[*(it + 2)]);
        scene.objects.push_back(triangle);
    }
}

void initializeCamera() {
    camera = Camera(eyeinit, upinit, center, fovy, w / (float) h);
//    camera = Camera(eyeinit, upinit, center, fovy, 1);
}

void init() {
    initializeScene();
    initializeCamera();
}

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: transforms scenefile [grader input (optional)]\n";
        exit(-1);
    }

    FreeImage_Initialise();
    readfile(argv[1]);
    w = 480;
    h = 480;
    init();
    RayTracer rayTracer;
    Image* image = rayTracer.raytrace(&camera, &scene, w, h);
    FIBITMAP *img = FreeImage_ConvertFromRawBits(image->data, w, h, w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);
    FreeImage_Save(FIF_PNG, img, "/Users/islamaliev/dev/testing/cpp/opengl/hw3/hw3/output.png", 0);

    FreeImage_DeInitialise();
    return 0;
}