#pragma once


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat4 mat4;

class Camera {
public:
    Camera(){};
    Camera(vec3 pos, vec3 upVec, vec3 lookAt, float fovy, float ratio): pos(pos) {
        forward = glm::normalize(pos - lookAt);
        right = glm::normalize(glm::cross(upVec, forward));
        up = glm::cross(forward, right);
//        this->fovy = (float) (fovy * M_PI / 360.f);
        this->fovy = fovy;
        this->fovx = this->fovy * ratio;
        m = glm::lookAt(pos, lookAt, upVec);
    }

    vec3 pos;
    vec3 forward;
    vec3 right;
    vec3 up;
    float fovy;
    float fovx;
    mat4 m;
};
