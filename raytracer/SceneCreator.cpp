#include "SceneCreator.h"
#include "Scene.h"
#include "SceneData.h"
#include "Triangle.h"
#include "Camera.h"
#include "Sphere.h"
#include "TriangleData.h"
#include "SphereData.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "PointLightData.h"
#include "DirectionalLightData.h"
#include "SceneDataDestructor.h"
#include "Plane.h"
#include "PlaneData.h"
#include "Box.h"
#include "BoxData.h"

Scene* SceneCreator::create(SceneData* sceneData) {
    this->sceneData = sceneData;
    scene = new Scene();
    initializeProperties();
    initializeObjects();
    initializeCamera();
    initializeLights();
    SceneDataDestructor().destruct(sceneData);
    return scene;
}

void SceneCreator::initializeObjects() {
    initializeTriangles();
    initializeSpheres();
    initializePlanes();
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
    for (auto it = sceneData->directionalLights.begin(); it != sceneData->directionalLights.end(); it++) {
        DirectionalLightData* data = *it;
        glm::vec3 color(data->color[0], data->color[1], data->color[2]);
        glm::vec3 position(data->direction[0], data->direction[1], data->direction[2]);
        DirectionalLight* light = new DirectionalLight(position, color);
        scene->lights.push_back(light);
    }
    std::copy(sceneData->attenuation, sceneData->attenuation + 3, scene->attenuation);
}

void SceneCreator::initializeProperties() {
    scene->width = sceneData->width;
    scene->height = sceneData->height;
    scene->maxDepth = sceneData->maxDepth;
    scene->outputFile = sceneData->outputFile;
}

void SceneCreator::initializeTriangles() {
    scene->verticies = sceneData->verticies;
    for (auto it = sceneData->triangles.begin(); it != sceneData->triangles.end(); it++) {
        TriangleData* const& data = *it;
        const glm::vec3& v1 = scene->verticies[data->indecies[0]];
        const glm::vec3& v2 = scene->verticies[data->indecies[1]];
        const glm::vec3& v3 = scene->verticies[data->indecies[2]];
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

void SceneCreator::initializePlanes() {
    for (auto it = sceneData->planes.begin(); it != sceneData->planes.end(); it++) {
        PlaneData* const& data = *it;
        Plane* plane = new Plane(glm::vec3(data->position[0], data->position[1], data->position[2]),
                glm::vec3(data->normal[0], data->normal[1], data->normal[2]), data->w, data->h, data->rotation);
        processAndAdd(data, plane);
    }
}

void SceneCreator::initializeBoxes() {
    for (auto it = sceneData->boxes.begin(); it != sceneData->boxes.end(); it++) {
        BoxData* const& data = *it;
        Box* box = new Box(glm::vec3(data->position[0], data->position[1], data->position[2]), data->size);
        processAndAdd(data, box);
    }
}

void SceneCreator::processAndAdd(ObjectData* data, Object* object) const {
    object->setTransform(data->transform);
    object->ambient = glm::vec3(data->ambient[0], data->ambient[1], data->ambient[2]);
    object->emission = glm::vec3(data->material.emission[0], data->material.emission[1], data->material.emission[2]);
    object->diffuse = glm::vec3(data->material.diffuse[0], data->material.diffuse[1], data->material.diffuse[2]);
    object->specular = glm::vec3(data->material.specular[0], data->material.specular[1], data->material.specular[2]);
    object->shininess = data->material.shininess;
    scene->objects.push_back(object);
}
