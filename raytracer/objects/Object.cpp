#include "Object.h"

void Object::setTransform(glm::mat4 matrix) {
    transform = matrix;
    inverseTransform = glm::inverse(transform);
}
