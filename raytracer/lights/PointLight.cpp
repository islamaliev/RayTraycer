#include <algorithm>
#include "PointLight.h"

PointLight::PointLight(const glm::vec3& pos, const Color& col, float attn[3])
    : Light(glm::vec4(pos, 1), col) {
    std::copy(attn, attn + 3, attenuation);
}

glm::vec3 PointLight::getDirectionTo(const glm::vec4& point) const {
    return glm::normalize(glm::vec3(position - point));
}

double PointLight::getDistanceTo(const glm::vec4& point) const {
    return glm::length(position - point);
}

bool PointLight::isCloserTo(const glm::vec4& point, const double& distance, const double& lightDistance) const {
    return distance == 0 || distance > lightDistance;
}

double PointLight::getFalloffAt(const double& distance) const {
    return attenuation[0] + attenuation[1] * distance + attenuation[2] * distance * distance;
}
