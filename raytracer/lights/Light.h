#pragma once


#include "glm/glm.hpp"

class Light {
public:
    Light(const glm::vec4& pos, const glm::vec3& col)
        : position(pos)
        , color(col) {
    }

    virtual ~Light() {};

    virtual glm::vec3 getDirectionTo(const glm::vec4& point) const = 0;

    virtual double getDistanceTo(const glm::vec4& point) const = 0;

    virtual double getFalloffAt(const double& distance) const = 0;

    virtual bool isCloserTo(const glm::vec4& point, const double& distance, const double& lightDistance) const = 0;

    glm::vec4 position;
    glm::vec3 color;
};