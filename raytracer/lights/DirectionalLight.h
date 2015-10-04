#pragma once


#include "Light.h"

class DirectionalLight : public Light {
public:
    DirectionalLight(const glm::vec3& pos, const glm::vec3& col)
        : Light(glm::vec4(glm::normalize(pos), 0), col) {
    }

    glm::vec3 getDirectionTo(const glm::vec4& point) const override;

    double getDistanceTo(const glm::vec4& point) const override;

    bool isCloserTo(const glm::vec4& point, const double& distance, const double& lightDistance) const override;

    double getFalloffAt(const double& distance) const override;
};
