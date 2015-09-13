#include "gmock/gmock.h"
#include "Triangle.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Ray.h"

using namespace testing;

const float DELTA = 0.02f;

const glm::vec3 V1 = vec3(1, 1, 0);
const glm::vec3 V2 = vec3(-1, -1, 0);
const glm::vec3 V3 = vec3(1, -1, 0);

class TriangleTest : public testing::Test {
public:
    TriangleTest()
        : triangle(&V1, &V2, &V3)
        , matrix(1.f) {}

    void SetUp() override {
        triangle.setTransform(matrix);
    }

    Triangle triangle;

private:
    glm::mat4 matrix;
};

class TriangleIntersectionTest : public TriangleTest {
public:
    void assertIntersection(float rayX, float rayY, float rayZ, float dirX, float dirY, float dirZ, float dist) {
        Ray* ray = new Ray();
        ray->pos = vec4(rayX, rayY, rayZ, 1);
        ray->dir = vec4(dirX, dirY, dirZ, 0);
        const float actDist = triangle.intersect(ray);
        EXPECT_TRUE(IntersectionMatch(ray, dist, actDist));
    }

private:
    ::testing::AssertionResult IntersectionMatch(Ray* ray, float expDist, float actDist) {
        if (fabsf(expDist - actDist) > DELTA) {
            const vec4& p = ray->pos;
            const vec4& d = ray->dir;
            return ::testing::AssertionFailure() << "ray(" << p.x << ", " << p.y << ", " << p.z << ") -> ("
                    << d.x << ", " << d.y << ", " << d.z << "), expected distanse: " << expDist
                    << ", actual: " << actDist;
        }
        return ::testing::AssertionSuccess();
    }
};

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