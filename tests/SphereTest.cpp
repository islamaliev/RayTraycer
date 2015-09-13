#include "gmock/gmock.h"
#include "Sphere.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace testing;

const float DELTA = 0.02f;

class SphereTest : public testing::Test {
public:
    SphereTest()
        : sphere(glm::vec3(), 1)
        , matrix(1.f) {}

    void SetUp() override {
        sphere.setTransform(matrix);
        transforms.clear();
    }

    void translate(float x, float y, float z) {
        matrix = glm::translate(matrix, glm::vec3(x, y, z));
        sphere.setTransform(matrix);
        std::stringstream s;
        s << "translate(" << x << ", " << y << ", " << z << ")";
        transforms.push_back(s.str());
    }

    void rotate(float degree, float x, float y, float z) {
        matrix = glm::rotate(matrix, degree, glm::vec3(x, y, z));
        sphere.setTransform(matrix);
        std::stringstream s;
        s << "rotate(" << degree << "˚, " << x << ", " << y << ", " << z << ")";
        transforms.push_back(s.str());
    }

    void scale(float x, float y, float z) {
        matrix = glm::scale(matrix, glm::vec3(x, y, z));
        sphere.setTransform(matrix);
        std::stringstream s;
        s << "scale(" << x << ", " << y << ", " << z << ")";
        transforms.push_back(s.str());
    }

    Sphere sphere;

protected:
    std::vector<std::string> transforms;

private:
    glm::mat4 matrix;
};

class SphereNormalTest : public SphereTest {
public:
    glm::vec3 getNormal(float x, float y, float z) {
        glm::vec4 point(x, y, z, 1);
        return sphere.getNormal(point);
    }

    void assertNormals(float x1, float y1, float z1, float x2, float y2, float z2) {
        glm::vec3 n = getNormal(x1, y1, z1);
        EXPECT_TRUE(NormalMatch(x1, y1, z1, n.x, n.y, n.z, x2, y2, z2));
    }

private:
    ::testing::AssertionResult NormalMatch(float px, float py, float pz, float x1, float y1, float z1, float x2, float y2, float z2) {
        const float d = fabsf(y1 - y2);
        if (fabsf(x1 - x2) > DELTA || d > DELTA || fabsf(z1 - z2) > DELTA) {
            return ::testing::AssertionFailure() << "point(" << px << ", " << py << ", " << pz
                    << ") -> expected(" << x2 << ", " << y2 << ", " << z2
                    << ") != actual(" << x1 << ", " << y1 << ", " << z1 << ")" << getTranslations();
        }

        return ::testing::AssertionSuccess();
    }

    std::string getTranslations() {
        std::string s("");
        if (transforms.size() > 0) {
            for (auto tr : transforms) {
                s += tr + " * ";
            }
            s = " | transorms: " + s.substr(0, s.size() - 2);
        }
        return s;
    }
};

TEST_F(SphereTest, Constructor) {
   ASSERT_EQ(sphere.position.x, 0);
   ASSERT_EQ(sphere.position.y, 0);
   ASSERT_EQ(sphere.position.z, 0);
}

TEST_F(SphereNormalTest, Default) {
    assertNormals(1, 0, 0, 1, 0, 0);
    assertNormals(0, 1, 0, 0, 1, 0);
    assertNormals(0, 0, -2, 0, 0, -1);
    assertNormals(-2, 0, 2, -0.707f, 0, 0.707f);
}

TEST_F(SphereNormalTest, TranslatedX) {
    translate(-2, 0, 0);
    assertNormals(-2.1f, 0, 0, -1, 0, 0);
    assertNormals(-2, 1, 0, 0, 1, 0);
    assertNormals(-2, 0, -2, 0, 0, -1);
    assertNormals(-4, 0, 2, -0.707f, 0, 0.707f);
}

TEST_F(SphereNormalTest, TranslatedY) {
    translate(0, 2, 0);
    assertNormals(1, 2, 0, 1, 0, 0);
    assertNormals(0, 3, 0, 0, 1, 0);
    assertNormals(0, 2, -2, 0, 0, -1);
    assertNormals(-2, 2, 2, -0.707f, 0, 0.707f);
}

TEST_F(SphereNormalTest, TranslatedZ) {
    translate(0, 0, -1);
    assertNormals(1, 0, -1, 1, 0, 0);
    assertNormals(0, 1, -1, 0, 1, 0);
    assertNormals(0, 0, -3, 0, 0, -1);
    assertNormals(-2, 0, 1, -0.707f, 0, 0.707f);
}

TEST_F(SphereNormalTest, Translated) {
    translate(2, -1, 1);
    assertNormals(3, -1, 1, 1, 0, 0);
    assertNormals(2, 0, 1, 0, 1, 0);
    assertNormals(2, -1, -1, 0, 0, -1);
    assertNormals(0, -1, 3, -0.707f, 0, 0.707f);
}

TEST_F(SphereNormalTest, Rotated) {
    rotate(90.f, 0, 0, 1);
    assertNormals(1, 0, 0, 1, 0, 0);
    rotate(90.f, 0, 1, 0);
    assertNormals(0, 1, 0, 0, 1, 0);
    rotate(90.f, 1, 0, 0);
    assertNormals(0, 0, -2, 0, 0, -1);
    rotate(90.f, -1, -1, 0);
    assertNormals(-2, 0, 2, -0.707f, 0, 0.707f);
}

TEST_F(SphereNormalTest, Scaled) {
    scale(2, 1, 1);
    assertNormals(2, 0, 0, 1, 0, 0);
    assertNormals(0, 2, 0, 0, 1, 0);
    scale(2000, 1, 1);
    assertNormals(5, 2, 0, 0, 1, 0);
}

TEST_F(SphereNormalTest, RotatedTranslated) {
    translate(-2, 0, 0);
    rotate(-90, 0, 0, 1);
    assertNormals(-1, 0, 0, 1, 0, 0);
    assertNormals(-3, 0, 0, -1, 0, 0);
    assertNormals(-2, 1, 0, 0, 1, 0);
    assertNormals(-2, -1, 0, 0, -1, 0);
}

TEST_F(SphereNormalTest, RotatedScaledTranslated) {
    translate(0, 2, 0);
    scale(2, 1, 1);
    rotate(180, 0, 0, 1);
    assertNormals(1, 2, 0, 1, 0, 0);
    assertNormals(0, 5, 0, 0, 1, 0);
}
