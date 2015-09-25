#pragma once


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class Camera {
public:
    Camera(){};

    Camera(const glm::vec3& pos, const glm::vec3& upVec, const glm::vec3& lookAt, float fovy, float ratio): pos(pos) {
        forward = glm::normalize(pos - lookAt);
        right = glm::normalize(glm::cross(upVec, forward));
        up = glm::cross(forward, right);
        this->fovy = fovy;
    }

    glm::vec3 pos;
    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;
    float fovy;
};
