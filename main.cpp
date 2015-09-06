#define MAINPROGRAM

#include <iostream>
#include "variables.h"
#include "readfile.h"
#include "FreeImage.h"
#include "raytracer/RayTracer.h"
#include "Image.h"
#include "TextParser.h"
#include "SceneCreator.h"

int main(int argc, const char * argv[]) {
    FreeImage_Initialise();
    readfile(argv[1]);
    w = 480;
    h = 480;

    TextParser parser;
    SceneData* const sceneData = parser.parse(argv[1]);
    SceneInitializer initializer;
    Scene* scene = initializer.create(sceneData);

    RayTracer rayTracer;
    Image* image = rayTracer.raytrace(scene, w, h);
    FIBITMAP *img = FreeImage_ConvertFromRawBits(image->data, w, h, w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);
    FreeImage_Save(FIF_PNG, img, "/Users/islamaliev/dev/testing/cpp/opengl/hw3/hw3/output.png", 0);

    FreeImage_DeInitialise();
    return 0;
}