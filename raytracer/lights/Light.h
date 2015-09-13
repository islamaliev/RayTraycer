#ifndef HW3_LIGHT_H
#define HW3_LIGHT_H


#include "glm/glm.hpp"

class Light {
public:
    Light(const glm::vec4& pos, const glm::vec3& col)
        : position(pos)
        , color(col) {
    }

    glm::vec4 position;
    glm::vec3 color;
};


#endif //HW3_LIGHT_H
