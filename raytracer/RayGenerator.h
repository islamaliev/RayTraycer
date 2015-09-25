#ifndef HW3_RAYGENERATOR_H
#define HW3_RAYGENERATOR_H

#include "glm/glm.hpp"

class Ray;

class RayGenerator {
public:
    Ray* generate(const glm::vec4& from, const glm::vec4& to);

    Ray* generate(const glm::vec4& from, const glm::vec3& along);

private:
    static const double SHOOT_OFFSET;
};


#endif //HW3_RAYGENERATOR_H
