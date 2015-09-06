#include "SceneCreator.h"
#include "Scene.h"
#include "SceneData.h"
#include "Triangle.h"
#include "Camera.h"

Scene* SceneInitializer::create(SceneData* sceneData) {
    this->sceneData = sceneData;
    scene = new Scene();
    initializeProperties();
    initializeObjects();
    initializeCamera();
    return scene;
}

void SceneInitializer::initializeObjects() {
    for (auto it = sceneData->indecies.begin(); it != sceneData->indecies.end(); it += 3) {
        const glm::vec3& v1 = sceneData->verticies[*it];
        const glm::vec3& v2 = sceneData->verticies[*(it + 1)];
        const glm::vec3& v3 = sceneData->verticies[*(it + 2)];
        Triangle* triangle = new Triangle(&v1, &v2, &v3);
        scene->objects.push_back(triangle);
    }
}

void SceneInitializer::initializeCamera() {
    const CameraData& cameraData = sceneData->camera;
    glm::vec3 pos(cameraData.lookFrom[0], cameraData.lookFrom[1], cameraData.lookFrom[2]);
    glm::vec3 lookAt(cameraData.lookAt[0], cameraData.lookAt[1], cameraData.lookAt[2]);
    glm::vec3 up(cameraData.up[0], cameraData.up[1], cameraData.up[2]);
    scene->camera = new Camera(pos, up, lookAt, cameraData.fovy, sceneData->width / (float) sceneData->height);
}

void SceneInitializer::initializeProperties() {
    scene->width = sceneData->width;
    scene->height = sceneData->height;
}
