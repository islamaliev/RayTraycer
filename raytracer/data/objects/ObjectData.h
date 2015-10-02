#pragma once


#include "glm/glm.hpp"
#include "MaterialData.h"

struct ObjectData {
    ObjectData()
        : transform(1.f)
    {};

    glm::mat4 transform;

    float ambient[3];

    MaterialData material;
};
