#include "BaseObjectTest.h"
#include "Sphere.h"

class SphereTest : public BaseObjectTest {
public:
    Object* createObject() override {
        return new Sphere(getTransform(), glm::vec3(), 1);
    }

    Sphere* getSphere() {
        return (Sphere*) object;
    }
};

class SphereNormalTest : public SphereTest {};

TEST_F(SphereTest, Constructor) {
   ASSERT_EQ(getSphere()->position.x, 0);
   ASSERT_EQ(getSphere()->position.y, 0);
   ASSERT_EQ(getSphere()->position.z, 0);
}

TEST_F(SphereNormalTest, Default) {
    assertNormal(1, 0, 0, 1, 0, 0);
    assertNormal(0, 1, 0, 0, 1, 0);
    assertNormal(0, 0, -2, 0, 0, -1);
    assertNormal(-2, 0, 2, -0.707f, 0, 0.707f);
}

TEST_F(SphereNormalTest, TranslatedX) {
    translate(-2, 0, 0);
    assertNormal(-2.1f, 0, 0, -1, 0, 0);
    assertNormal(-2, 1, 0, 0, 1, 0);
    assertNormal(-2, 0, -2, 0, 0, -1);
    assertNormal(-4, 0, 2, -0.707f, 0, 0.707f);
}

TEST_F(SphereNormalTest, TranslatedY) {
    translate(0, 2, 0);
    assertNormal(1, 2, 0, 1, 0, 0);
    assertNormal(0, 3, 0, 0, 1, 0);
    assertNormal(0, 2, -2, 0, 0, -1);
    assertNormal(-2, 2, 2, -0.707f, 0, 0.707f);
}

TEST_F(SphereNormalTest, TranslatedZ) {
    translate(0, 0, -1);
    assertNormal(1, 0, -1, 1, 0, 0);
    assertNormal(0, 1, -1, 0, 1, 0);
    assertNormal(0, 0, -3, 0, 0, -1);
    assertNormal(-2, 0, 1, -0.707f, 0, 0.707f);
}

TEST_F(SphereNormalTest, Translated) {
    translate(2, -1, 1);
    assertNormal(3, -1, 1, 1, 0, 0);
    assertNormal(2, 0, 1, 0, 1, 0);
    assertNormal(2, -1, -1, 0, 0, -1);
    assertNormal(0, -1, 3, -0.707f, 0, 0.707f);
}

TEST_F(SphereNormalTest, Rotated) {
    rotate(90.f, 0, 0, 1);
    assertNormal(1, 0, 0, 1, 0, 0);
    rotate(90.f, 0, 1, 0);
    assertNormal(0, 1, 0, 0, 1, 0);
    rotate(90.f, 1, 0, 0);
    assertNormal(0, 0, -2, 0, 0, -1);
    rotate(90.f, -1, -1, 0);
    assertNormal(-2, 0, 2, -0.707f, 0, 0.707f);
}

TEST_F(SphereNormalTest, Scaled) {
    scale(2, 1, 1);
    assertNormal(2, 0, 0, 1, 0, 0);
    assertNormal(0, 2, 0, 0, 1, 0);
    scale(2000, 1, 1);
    assertNormal(5, 2, 0, 0, 1, 0);
}

TEST_F(SphereNormalTest, RotatedTranslated) {
    rotate(-90, 0, 0, 1);
    translate(-2, 0, 0);
    assertNormal(-1, 0, 0, 1, 0, 0);
    assertNormal(-3, 0, 0, -1, 0, 0);
    assertNormal(-2, 1, 0, 0, 1, 0);
    assertNormal(-2, -1, 0, 0, -1, 0);
}

TEST_F(SphereNormalTest, RotatedScaledTranslated) {
    rotate(180, 0, 0, 1);
    scale(2, 1, 1);
    translate(0, 2, 0);
    assertNormal(1, 2, 0, 1, 0, 0);
    assertNormal(0, 5, 0, 0, 1, 0);
}
