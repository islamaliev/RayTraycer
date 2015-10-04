#pragma once


#include "glm/glm.hpp"
#include "Color.h"

class Ray;

class Object {
public:
    Object(const glm::mat4& m);

    virtual ~Object() {};

    virtual double intersect(const Ray* ray) const { return 0; }

    virtual glm::vec3 getNormal(const glm::vec4& point) const = 0;

    const glm::mat4& getTransform() const { return transform; }
    void setTransform(const glm::mat4& matrix);

    const glm::mat4& getInverseTransform() const { return inverseTransform; }

    Color ambient;
    Color diffuse;
    Color specular;
    Color emission;
    float shininess;

protected:
    typedef glm::vec3 vec3;
    typedef glm::vec4 vec4;
    typedef glm::mat4 mat4;

private:
    glm::mat4 transform;
    glm::mat4 inverseTransform;
};