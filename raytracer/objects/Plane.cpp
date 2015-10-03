#include "Plane.h"
#include "Ray.h"
#include "glm/gtc/matrix_transform.hpp"

Plane::Plane(const mat4& m, const glm::vec3& pos, const glm::vec3& norm, float w, float h, float rotation)
    : Object(m)
    , position(pos, 1)
    , localNormal(vec4(glm::normalize(norm), 0))
    , w(w)
    , h(h)
    , rotation(rotation) {
    double dot = glm::dot(vec3(0, 0, 1), vec3(localNormal));
    if (dot != 1)
    {
        mat4 tr = getTransform();
        vec3 rotAxis = glm::cross(vec3(0, 0, 1), vec3(localNormal));
        double angle = acos(dot);
        mat4 rotM = glm::rotate(mat4(1), angle * 180 / M_PI, rotAxis);

        setTransform(glm::rotate(tr, angle * 180 / M_PI, rotAxis));
    }
    vec3 transformedNormal = vec3(glm::transpose(getInverseTransform()) * localNormal);
    normal = glm::normalize(transformedNormal);
//    const vec3& transformedNormal = vec3(getTransform() * localNormal);
//    normal = glm::normalize(vec3(localNormal));
}

double Plane::intersect(const Ray* ray) const {
    const mat4& invM = getInverseTransform();

    vec4 localRayPos = invM * ray->pos;
    vec4 localRayDir = invM * ray->dir;

    double d = glm::dot(localRayDir, localNormal);
    if (d == 0) {
        return 0;
    }

    vec4 p0l0 = position - localRayPos;
    double t = glm::dot(p0l0, localNormal) / d;
    if (t <= 0) {
        return 0;
    }

    vec4 p(localRayPos + localRayDir * t);
    if (isPointInBounds(p)) {
        p = ray->pos - getTransform() * p;
        return glm::length(p);
    }

    return 0;

    /*vec4 a(*verticies[0], 0);

    double t = (glm::dot(a, localNormal) - glm::dot(localRayPos, localNormal)) / d;
    if (t < 0) {
        return 0;
    }

    vec4 p(localRayPos + (localRayDir * t));
    if (isPointInTriangle(vec3(p), *verticies[0], *verticies[2], *verticies[1]))
    {
        p = ray->pos - getTransform() * p;
        return glm::length(p);
    }*/


    return 0;
}

glm::vec3 Plane::getNormal(const glm::vec4& point) const {
    return normal;
}

bool Plane::isPointInBounds(const glm::vec4& p) const {
    double angle = rotation * M_PI / 360.0;
    double x = p.x + w / 2;// * cos(angle);
    double y = p.y + h / 2;// * -sin(angle);
    return (x >= 0 && x <= w && y >= 0 && y <= h);
}
