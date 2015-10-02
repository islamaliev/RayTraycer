#pragma once


#include "glm/glm.hpp"

class Light {
public:
    Light(const glm::vec4& pos, const glm::vec3& col)
        : position(pos)
        , color(col) {
    }

    virtual ~Light() {};

    glm::vec4 position;
    glm::vec3 color;
};
