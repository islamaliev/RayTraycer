#ifdef MAINPROGRAM
#define EXTERN
#else
#define EXTERN extern
#endif

#include "glm/glm.hpp"
#include <vector>

EXTERN glm::vec3 eye;
EXTERN glm::vec3 up;

EXTERN glm::vec3 eyeinit;
EXTERN glm::vec3 upinit;
EXTERN glm::vec3 center;
EXTERN int w, h;
EXTERN float fovy;

EXTERN struct LightData {
    explicit LightData(bool direct, float* data): dir(data[0], data[1], data[2], 1), color(data[4], data[5], data[6]) {
        if (direct) {
            dir.w = 0;
        }
    }

    glm::vec4 dir;
    glm::vec3 color;
};

EXTERN std::vector<LightData> lights;

EXTERN int maxverts;
EXTERN std::vector<glm::vec3> verticies;
EXTERN std::vector<unsigned> indecies;

EXTERN float ambient[3];
EXTERN float diffuse[3];
EXTERN float specular[3];
EXTERN float emission[3];
EXTERN float shininess;
