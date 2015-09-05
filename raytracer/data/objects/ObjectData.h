#ifndef HW3_OBJECTDATA_H
#define HW3_OBJECTDATA_H


#include "glm/glm.hpp"

struct ObjectData {
    ObjectData(): transform(1.f) {};

    glm::mat4 transform;
};


#endif //HW3_OBJECTDATA_H
