#include "Box.h"
#include "Ray.h"

Box::Box(const glm::mat4& m, const glm::vec3& pos, float size)
        : Object(m)
        , position(pos, 1)
        , size(size) {}

double Box::intersect(const Ray* ray) const {
    return 0;
}

glm::vec3 Box::getNormal(const glm::vec4& point) const {
    return vec3();
}
