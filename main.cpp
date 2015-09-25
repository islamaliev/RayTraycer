#include <iostream>
#include "FreeImage.h"
#include "RayTracer.h"
#include "Image.h"
#include "TextParser.h"
#include "SceneCreator.h"
#include "Scene.h"
#include "SceneData.h"
#include "SceneDestructor.h"

int main(int argc, const char * argv[]) {
    FreeImage_Initialise();

    TextParser parser;
    SceneData* const sceneData = parser.parse(argv[1]);

    SceneCreator sceneCreator;
    Scene* scene = sceneCreator.create(sceneData);

    RayTracer rayTracer;
    Image* image = rayTracer.raytrace(scene);
    FIBITMAP *img = FreeImage_ConvertFromRawBits(image->data, scene->width, scene->height, scene->width * 3,
            24, 0xFF0000, 0x00FF00, 0x0000FF, true);
    std::string filename = "/Users/islamaliev/dev/testing/cpp/opengl/hw3/hw3/" + scene->outputFile;
    FreeImage_Save(FIF_PNG, img, filename.c_str(), 0);

    FreeImage_DeInitialise();
    SceneDestructor().destruct(scene);
    delete image;
    return 0;
}