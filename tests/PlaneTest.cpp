#include "Plane.h"
#include "BaseObjectTest.h"


class PlaneTest : public BaseObjectTest {
public:
    Object* createObject() override {
        return new Plane(getTransform(), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), 1, 1, 0);
    }

    Plane* getPlane() {
        return (Plane*) object;
    }
};

class PlaneNormalTest : public PlaneTest {};

TEST_F(PlaneNormalTest, Default) {
    assertNormal(0, 0, 1);
}

TEST_F(PlaneNormalTest, Rotated) {
    rotate(45, 1, 0, 0);
    assertNormal(0, -0.707f, 0.707);
    rotate(45, -1, 0, 0);
    rotate(45, 0, 1, 0);
    assertNormal(0.707, 0, 0.707);
    rotate(45, 0, 1, 0);
    assertNormal(1, 0, 0);
}

TEST_F(PlaneNormalTest, Translated) {
    translate(1, 0, 0);
    assertNormal(0, 0, 1);
    translate(4, -8, 2.5);
    assertNormal(0, 0, 1);
}

TEST_F(PlaneNormalTest, Scaled) {
    scale(4, 1, 1);
    assertNormal(0, 0, 1);
    scale(0.01, 4, 1.5);
    assertNormal(0, 0, 1);
}

TEST_F(PlaneNormalTest, ScaledRotatedTranslated) {
    scale(4, 1, 1);
    translate(4, -8, 2.5);
    rotate(45, 1, 0, 0);
    assertNormal(0, -0.707f, 0.707);
}
