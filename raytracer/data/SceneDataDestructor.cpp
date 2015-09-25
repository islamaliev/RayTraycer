#include "SceneDataDestructor.h"
#include <vector>
#include "SceneData.h"
#include "TriangleData.h"
#include "SphereData.h"
#include "PointLightData.h"
#include "DirectionalLightData.h"

namespace {
    template <class T>
    void clearVector(std::vector<T>& vec) {
        for (auto it = vec.rbegin(); it != vec.rend(); it++) {
            delete *it;
        }
        vec.clear();
    }
}

void SceneDataDestructor::destruct(SceneData* sceneData) {
    sceneData->verticies.clear();
    clearVector(sceneData->triangles);
    clearVector(sceneData->spheres);
    clearVector(sceneData->pointLights);
    clearVector(sceneData->directionalLights);
    delete sceneData;
}
