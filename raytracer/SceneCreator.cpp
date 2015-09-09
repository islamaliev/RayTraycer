#include "SceneCreator.h"
#include "Scene.h"
#include "SceneData.h"
#include "Triangle.h"
#include "Camera.h"
#include "Sphere.h"
#include "TriangleData.h"
#include "SphereData.h"
#include "PointLight.h"
#include "PointLightData.h"

Scene* SceneCreator::create(SceneData* sceneData) {
    this->sceneData = sceneData;
    scene = new Scene();
    initializeProperties();
    initializeObjects();
    initializeCamera();
    initializeLights();
    return scene;
}

void SceneCreator::initializeObjects() {
    initializeTriangles();
    initializeSpheres();
}

void SceneCreator::initializeCamera() {
    const CameraData& cameraData = sceneData->camera;
    glm::vec3 pos(cameraData.lookFrom[0], cameraData.lookFrom[1], cameraData.lookFrom[2]);
    glm::vec3 lookAt(cameraData.lookAt[0], cameraData.lookAt[1], cameraData.lookAt[2]);
    glm::vec3 up(cameraData.up[0], cameraData.up[1], cameraData.up[2]);
    scene->camera = new Camera(pos, up, lookAt, cameraData.fovy, sceneData->width / (float) sceneData->height);
}

void SceneCreator::initializeLights() {
    for (auto it = sceneData->pointLights.begin(); it != sceneData->pointLights.end(); it++) {
        PointLightData* data = *it;
        glm::vec3 color(data->color[0], data->color[1], data->color[2]);
        glm::vec3 position(data->position[0], data->position[1], data->position[2]);
        PointLight* light = new PointLight(position, color);
        scene->lights.push_back(light);
    }
}

void SceneCreator::initializeProperties() {
    scene->width = sceneData->width / 2;
    scene->height = sceneData->height / 2;
}

void SceneCreator::initializeTriangles() {
    for (auto it = sceneData->triangles.begin(); it != sceneData->triangles.end(); it++) {
        TriangleData* const& data = *it;
        const glm::vec3& v1 = sceneData->verticies[data->indecies[0]];
        const glm::vec3& v2 = sceneData->verticies[data->indecies[1]];
        const glm::vec3& v3 = sceneData->verticies[data->indecies[2]];
        processAndAdd(data, new Triangle(&v1, &v2, &v3));
    }
}

void SceneCreator::initializeSpheres() {
    for (auto it = sceneData->spheres.begin(); it != sceneData->spheres.end(); it++) {
        SphereData* const& data = *it;
        Sphere* sphere = new Sphere(glm::vec3(data->position[0], data->position[1], data->position[2]), data->radius);
        processAndAdd(data, sphere);
    }
}

void SceneCreator::processAndAdd(ObjectData* data, Object* object) const {
    std::copy(data->ambient, data->ambient + 3, object->ambient);
    object->setTransform(data->transform);
    std::copy(data->material.emission, data->material.emission + 3, object->emission);
    std::copy(data->material.diffuse, data->material.diffuse + 3, object->diffuse);
    std::copy(data->material.specular, data->material.specular + 3, object->specular);
    object->shininess = data->material.shininess;
    scene->objects.push_back(object);
}
