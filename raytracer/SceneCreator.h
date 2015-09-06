#ifndef HW3_SCENEINITIALIZER_H
#define HW3_SCENEINITIALIZER_H

#include "ObjectData.h"
#include "Object.h"

class Scene;
class SceneData;

class SceneInitializer {
public:
    SceneInitializer()
            : scene(nullptr)
            , sceneData(nullptr)
    {}

    ~SceneInitializer() {
        scene = nullptr;
        sceneData = nullptr;
    }

    Scene* create(SceneData* sceneData);

private:
    void initializeObjects();

    void initializeCamera();

    void initializeTriangles();

    void initializeSpheres();

    void initializeProperties();

    void processAndAdd(ObjectData* data, Object* object) const;

    Scene* scene;
    SceneData* sceneData;
};


#endif //HW3_SCENEINITIALIZER_H
