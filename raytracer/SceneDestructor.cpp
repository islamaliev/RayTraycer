#include "SceneDestructor.h"
#include "Scene.h"
#include "Object.h"
#include "Light.h"
#include "Camera.h"

namespace {
    template <class T>
    void clearVector(std::vector<T>& vec) {
        for (auto it = vec.rbegin(); it != vec.rend(); it++) {
            delete *it;
        }
        vec.clear();
    }
}

void SceneDestructor::destruct(Scene* scene) {
    scene->verticies.clear();

    clearVector(scene->objects);
    clearVector(scene->lights);

    delete scene->camera;
    delete scene;
}
