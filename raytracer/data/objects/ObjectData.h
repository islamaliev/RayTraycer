#ifndef HW3_OBJECTDATA_H
#define HW3_OBJECTDATA_H


#include "glm/glm.hpp"
#include "MaterialData.h"

struct ObjectData {
    ObjectData(): transform(1.f) {};

    glm::mat4 transform;

    float ambient[3];

    MaterialData material;
};


#endif //HW3_OBJECTDATA_H
