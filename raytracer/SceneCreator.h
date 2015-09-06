#ifndef HW3_SCENEINITIALIZER_H
#define HW3_SCENEINITIALIZER_H

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

    Scene* scene;
    SceneData* sceneData;

    void initializeProperties();
};


#endif //HW3_SCENEINITIALIZER_H
