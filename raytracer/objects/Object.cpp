#include "Object.h"

void Object::setTransform(const glm::mat4& matrix) {
    transform = matrix;
    inverseTransform = glm::inverse(transform);
}
