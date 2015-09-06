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
    void initializeScene();

    void initializeCamera();

    Scene* scene;
    SceneData* sceneData;
};


#endif //HW3_SCENEINITIALIZER_H
