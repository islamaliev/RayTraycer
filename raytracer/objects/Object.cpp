#include "Object.h"

void Object::setTransform(const glm::mat4& matrix) {
    transform = matrix;
    inverseTransform = glm::inverse(transform);
}

Object::Object(const glm::mat4& m)
    : transform(m) {
    inverseTransform = glm::inverse(transform);
}
