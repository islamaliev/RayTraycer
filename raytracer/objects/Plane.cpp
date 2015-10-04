#include "Plane.h"
#include "Ray.h"
#include "glm/gtc/matrix_transform.hpp"

const glm::vec3 Plane::DEFAULT_NORMAL = glm::vec3(0, 0, 1);
const glm::vec4 Plane::DEFAULT_NORMAL_4 = glm::vec4(DEFAULT_NORMAL, 0);

Plane::Plane(const mat4& m, const glm::vec3& pos, const glm::vec3& norm, float w, float h, float rotation)
    : Object(m)
    , w(w)
    , h(h)
    , rotation(rotation) {
    init(pos, norm);
}

void Plane::init(const glm::vec3& pos, const glm::vec3& norm) {
    const glm::vec3& localNormal = glm::normalize(norm);
    double dot = glm::dot(DEFAULT_NORMAL, localNormal);
    glm::mat4 matrix = glm::translate(getTransform(), pos);
    if (dot != 1) {
        if (dot != -1) {
            const vec3& rotAxis = glm::cross(DEFAULT_NORMAL, localNormal);
            matrix = glm::rotate(matrix, acos(dot) * 180 / M_PI, rotAxis);
        } else {
            matrix = glm::rotate(matrix, 180.0, vec3(0, 1, 0));
        }
    }
    if (rotation != 0) {
        matrix = glm::rotate(matrix, (double) rotation, DEFAULT_NORMAL);
    }
    setTransform(matrix);
    const vec4& transformedNormal = getTransform() * vec4(DEFAULT_NORMAL, 0);
    normal = glm::normalize(vec3(transformedNormal));
}

double Plane::intersect(const Ray* ray) const {
    const mat4& invM = getInverseTransform();

    const vec4& localRayPos = invM * ray->pos;
    const vec4& localRayDir = invM * ray->dir;

    double d = glm::dot(DEFAULT_NORMAL_4, localRayDir);
    if (fabs(d) < 0.0001f) {
        return 0;
    }
    double t = glm::dot(-localRayPos, DEFAULT_NORMAL_4) / d;
    if (t < 0) {
        return 0;
    }

    vec4 p(localRayPos + (localRayDir * t));
    if (isPointInBounds(p)) {
        p = ray->pos - getTransform() * p;
        return glm::length(p);
    }

    return 0;
}

glm::vec3 Plane::getNormal(const glm::vec4& point) const {
    return normal;
}

bool Plane::isPointInBounds(const glm::vec4& p) const {
    double x = p.x + w * 0.5;
    double y = p.y + h * 0.5;
    return (x >= 0 && x <= w && y >= 0 && y <= h);
}
