#pragma once


#include "Light.h"

class PointLight : public Light {
public:
    PointLight(const glm::vec3& pos, const Color& col, float attn[3]);

    glm::vec3 getDirectionTo(const glm::vec4& point) const override;

    double getDistanceTo(const glm::vec4& point) const override;

    bool isCloserTo(const glm::vec4& point, const double& distance, const double& lightDistance) const override;

    double getFalloffAt(const double& distance) const override ;

    float attenuation[3];
};
