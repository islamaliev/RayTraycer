#include <vector>
#include "Triangle.h"
#include "BaseObjectTest.h"

const glm::vec3 V1 = glm::vec3(1, 1, 0);
const glm::vec3 V2 = glm::vec3(-1, -1, 0);
const glm::vec3 V3 = glm::vec3(1, -1, 0);

class TriangleTest : public BaseObjectTest {
public:
    Object* createObject() override {
        return new Triangle(glm::mat4(1), &V1, &V2, &V3);
    };

    Triangle* getTriangle() {
        return (Triangle*) object;
    }
};

class TriangleIntersectionTest : public TriangleTest {};

class TriangleNormalTest : public TriangleTest {};

TEST_F(TriangleIntersectionTest, PerpendicularRay) {
    assertIntersection(0.5f, -0.5f, 1, 0, 0, -1, 1);
    assertIntersection(0.1f, 0, 1, 0, 0, -1, 1);
    assertIntersection(-0.1f, 0.1f, 1, 0, 0, -1, 0);
    assertIntersection(0, -1.1f, 1, 0, 0, -1, 0);
    assertIntersection(1.1f, 0, 1, 0, 0, -1, 0);
}

TEST_F(TriangleIntersectionTest, ParallelRay) {
    assertIntersection(0, 2.f, 0, 0, -1.f, 0, 0);
    assertIntersection(0, 2.f, 0, 1, -1.f, 0, 0);
}

TEST_F(TriangleIntersectionTest, ArbitraryRay) {
    assertIntersection(0.2f, -1.2f, 1.f, 0, 0.7071f, -0.7071f, 1.4142f);
    assertIntersection(0, 0, 1.f, 0, -0.708f, -0.708f, 0);
}

TEST_F(TriangleNormalTest, Default) {
    assertNormal(0, 0, 1);
}
