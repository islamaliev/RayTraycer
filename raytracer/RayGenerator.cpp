#include "RayGenerator.h"
#include "Ray.h"

const double RayGenerator::SHOOT_OFFSET = 0.00000001;

Ray* RayGenerator::generate(const glm::vec4& from, const glm::vec4& to) {
    if (to.w == 0) {
        return generate(from, glm::vec3(to));
    } else {
        glm::vec3 dir = glm::vec3(to - from);
        return generate(from, glm::normalize(dir));
    }
}

Ray* RayGenerator::generate(const glm::vec4& from, const glm::vec3& along) {
    Ray* ray = new Ray();
    ray->dir = glm::vec4(along, 0);
    ray->pos = from + ray->dir * SHOOT_OFFSET;
    return ray;
}
