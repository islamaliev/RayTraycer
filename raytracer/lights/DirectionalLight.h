#ifndef HW3_DIRECTIONALLIGHT_H
#define HW3_DIRECTIONALLIGHT_H


#include "Light.h"

class DirectionalLight : public Light {
public:
    DirectionalLight(const glm::vec3& pos, const glm::vec3& col)
        : Light(glm::vec4(glm::normalize(pos), 0), col) {
    }
};


#endif //HW3_DIRECTIONALLIGHT_H
