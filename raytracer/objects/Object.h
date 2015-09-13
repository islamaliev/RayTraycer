#pragma once


#include "glm/glm.hpp"

class Ray;

class Object {
public:
    Object()
        : transform(1.f)
        , inverseTransform(1.f)
    {}

    virtual float intersect(const Ray* ray) const { return 0; }

    virtual glm::vec3 getNormal(glm::vec4 point) = 0;

    const glm::mat4& getTransform() const { return transform; }
    void setTransform(glm::mat4 matrix);

    const glm::mat4& getInverseTransform() const { return inverseTransform; }

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 emission;
    float shininess;

protected:
    typedef glm::vec3 vec3;
    typedef glm::vec4 vec4;
    typedef glm::mat4 mat4;

private:
    glm::mat4 transform;
    glm::mat4 inverseTransform;
};