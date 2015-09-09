#ifndef HW3_LIGHT_H
#define HW3_LIGHT_H


#include "glm/glm.hpp"

class Light {
public:
    Light(const glm::vec3& col)
        : color(col) {
    }

    glm::vec3 color;
};


#endif //HW3_LIGHT_H
