#include "DirectionalLight.h"

glm::vec3 DirectionalLight::getDirectionTo(const glm::vec4& point) const {
    return glm::vec3(position);
}

double DirectionalLight::getDistanceTo(const glm::vec4& point) const {
    return 0;
}

bool DirectionalLight::isCloserTo(const glm::vec4& point, const double& distance, const double& lightDistance) const {
    return distance == 0;
}

double DirectionalLight::getFalloffAt(const double& distance) const {
    return 1;
}
