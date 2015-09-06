#include "SceneCreator.h"
#include "Scene.h"
#include "SceneData.h"
#include "Triangle.h"
#include "Camera.h"
#include "Sphere.h"

Scene* SceneInitializer::create(SceneData* sceneData) {
    this->sceneData = sceneData;
    scene = new Scene();
    initializeProperties();
    initializeObjects();
    initializeCamera();
    return scene;
}

void SceneInitializer::initializeObjects() {
    initializeTriangles();
    initializeSpheres();
}

void SceneInitializer::initializeCamera() {
    const CameraData& cameraData = sceneData->camera;
    glm::vec3 pos(cameraData.lookFrom[0], cameraData.lookFrom[1], cameraData.lookFrom[2]);
    glm::vec3 lookAt(cameraData.lookAt[0], cameraData.lookAt[1], cameraData.lookAt[2]);
    glm::vec3 up(cameraData.up[0], cameraData.up[1], cameraData.up[2]);
    scene->camera = new Camera(pos, up, lookAt, cameraData.fovy, sceneData->width / (float) sceneData->height);
}

void SceneInitializer::initializeProperties() {
    scene->width = sceneData->width / 2;
    scene->height = sceneData->height / 2;
}

void SceneInitializer::initializeTriangles() {
    for (auto it = sceneData->triangles.begin(); it != sceneData->triangles.end(); it++) {
        TriangleData* const& data = *it;
        const glm::vec3& v1 = sceneData->verticies[data->indecies[0]];
        const glm::vec3& v2 = sceneData->verticies[data->indecies[1]];
        const glm::vec3& v3 = sceneData->verticies[data->indecies[2]];
        processAndAdd(data, new Triangle(&v1, &v2, &v3));
    }
}

void SceneInitializer::initializeSpheres() {
    for (auto it = sceneData->spheres.begin(); it != sceneData->spheres.end(); it++) {
        SphereData* const& data = *it;
        Sphere* sphere = new Sphere(glm::vec3(data->position[0], data->position[1], data->position[2]), data->radius);
        processAndAdd(data, sphere);
    }
}

void SceneInitializer::processAndAdd(ObjectData* data, Object* object) const {
    std::copy(data->ambient, data->ambient + 3, object->ambient);
    object->transform = data->transform;
    scene->objects.push_back(object);
}
