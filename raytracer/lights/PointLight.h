#ifndef HW3_POINTLIGHT_H
#define HW3_POINTLIGHT_H


#include "Light.h"

class PointLight : public Light {
public:
    PointLight(const glm::vec3& pos, const glm::vec3& col)
        : Light(col)
        , position(pos, 1) {
    }

    glm::vec4 position;
};


#endif //HW3_POINTLIGHT_H
