#pragma once


#include "Light.h"

class PointLight : public Light {
public:
    PointLight(const glm::vec3& pos, const glm::vec3& col)
        : Light(glm::vec4(pos, 1), col) {
    }
};
