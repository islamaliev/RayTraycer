#ifndef HW3_POINTLIGHT_H
#define HW3_POINTLIGHT_H


#include "Light.h"

class PointLight : public Light {
public:
    PointLight(const glm::vec3& pos, const glm::vec3& col)
        : Light(glm::vec4(pos, 1), col) {
    }
};


#endif //HW3_POINTLIGHT_H
