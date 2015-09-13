#ifndef HW3_COLORCALCULATOR_H
#define HW3_COLORCALCULATOR_H


//namespace glm {
//    class vec3;
//}

#include "glm/glm.hpp"

class Intersection;
class Scene;

class ColorCalculator {
public:
    ColorCalculator(Scene* const scene)
        : scene(scene) {
    }

    unsigned calculate(const Intersection* intersection) const;

private:
    unsigned convertToInt(float chanels[3]) const;
    glm::vec4 convertToVec(float chanels[3]) const;

    Scene* const scene;
};


#endif //HW3_COLORCALCULATOR_H
