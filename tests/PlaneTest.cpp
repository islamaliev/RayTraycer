#include "Plane.h"
#include "BaseObjectTest.h"


class PlaneTest : public BaseObjectTest {
public:
    Object* createObject() override {
        return new Plane(getTransform(), glm::vec3(0, 0, 0), Plane::DEFAULT_NORMAL, 1, 1, 0);
    }

    void setNewPlane(float posX, float posY, float posZ, float nX, float nY, float nZ, float rotation = 0) {
        setNewObject(new Plane(glm::mat4(1), glm::vec3(posX, posY, posZ), glm::vec3(nX, nY, nZ), 1, 1, rotation));
    }

    Plane* getPlane() {
        return (Plane*) object;
    }
};

class PlaneNormalTest : public PlaneTest {};

class PlaneIntersectionTest : public PlaneTest {};

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

TEST_F(PlaneIntersectionTest, PerpendicularRay) {
    assertIntersection( 0,     0,    1, 0, 0, -1, 1);
    assertIntersection( 0.4f,  0.4f, 1, 0, 0, -1, 1);
    assertIntersection(-0.4f,  0.4f, 1, 0, 0, -1, 1);
    assertIntersection(-0.4f, -0.4f, 1, 0, 0, -1, 1);
    assertIntersection( 0.4f, -0.4f, 1, 0, 0, -1, 1);
    assertIntersection( 0.6f,  0,    1, 0, 0, -1, 0);
    assertIntersection(-0.6f,  0,    1, 0, 0, -1, 0);
    assertIntersection( 0,    -0.6f, 1, 0, 0, -1, 0);
    assertIntersection( 0,     0.6f, 1, 0, 0, -1, 0);
}

TEST_F(PlaneIntersectionTest, ParallelRay) {
    assertIntersection(0, 2.f, 0, 0, -1.f, 0, 0);
    assertIntersection(0, 2.f, 0, 1, -1.f, 0, 0);
}

TEST_F(PlaneIntersectionTest, ArbitraryRay) {
    assertIntersection(0.2f, -1.2f, 1.f, 0,  0.7071f, -0.7071f, 1.4142f);
    assertIntersection(0,     0,    1.f, 0, -0.708f, - 0.708f,  0);
}

TEST_F(PlaneIntersectionTest, ArbitraryRayWithLocalNormal) {
    setNewPlane(0, 0, 0, 0, 0, 1);
    assertIntersection(0, -3, -1, 0, 0.7071f, -0.7071f, 0);
    setNewPlane(0, 0, 0, 0, 1, 0);
    assertIntersection(0, -1, 3, 0, -0.7071f, -0.7071f, 0);
}

TEST_F(PlaneIntersectionTest, RotatedPlane) {
    rotate(90, -1, 0, 0);
    assertIntersection( 0, 0.1f, 1,    0,  0, -1, 0);
    assertIntersection( 0, 1,    0.1f, 0, -1,  0, 1);
}

TEST_F(PlaneNormalTest, LocalPosition) {
    setNewPlane(0, -1, 0, 0, 0, 1);
    assertNormal(0, 0, 1);
    setNewPlane(1, 0, 2, 0, 0, 1);
    assertNormal(0, 0, 1);
}

TEST_F(PlaneNormalTest, LocalNormal) {
    setNewPlane(0, 0, 0, 1, 0, 0);
    assertNormal(1, 0, 0);
    setNewPlane(0, 0, 0, 0, 1, 0);
    assertNormal(0, 1, 0);
}

TEST_F(PlaneNormalTest, RotationAndLocalNormal) {
    setNewPlane(0, 0, 0, 1, 0, 0);
    rotate(90, 0, 0, 1);
    assertNormal(0, 1, 0);
    rotate(45, 1, 0, 0);
    assertNormal(0, 0.707, 0.707);
}

TEST_F(PlaneIntersectionTest, LocalRotation) {
    setNewPlane(0, 0, 0, 0, 0, 1, 45);
    assertIntersection( 0,     0,    1, 0, 0, -1, 1);
    assertIntersection( 0.4f,  0.4f, 1, 0, 0, -1, 0);
    assertIntersection(-0.4f,  0.4f, 1, 0, 0, -1, 0);
    assertIntersection(-0.4f, -0.4f, 1, 0, 0, -1, 0);
    assertIntersection( 0.4f, -0.4f, 1, 0, 0, -1, 0);
    assertIntersection( 0.6f,  0,    1, 0, 0, -1, 1);
    assertIntersection(-0.6f,  0,    1, 0, 0, -1, 1);
    assertIntersection( 0,    -0.6f, 1, 0, 0, -1, 1);
    assertIntersection( 0,     0.6f, 1, 0, 0, -1, 1);
}

TEST_F(PlaneIntersectionTest, RotationWithLocalPositionNormalAndRotation) {
    setNewPlane(0, 0, 0, 0, 0.7071, -0.7071f, 45);
    rotate(45, 1, 0, 0);
    translate(1, 0, 0);
    assertNormal(0, 1, 0);
    assertIntersection(1,    1,  0,    0, -1, 0, 1);
    assertIntersection(1.4f, 1,  0.4f, 0, -1, 0, 0);
    assertIntersection(0.6f, 1,  0.4f, 0, -1, 0, 0);
    assertIntersection(0.6f, 1, -0.4f, 0, -1, 0, 0);
    assertIntersection(1.4f, 1, -0.4f, 0, -1, 0, 0);
    assertIntersection(1.6f, 1,  0,    0, -1, 0, 1);
    assertIntersection(0.4f, 1,  0,    0, -1, 0, 1);
    assertIntersection(1,    1, -0.6f, 0, -1, 0, 1);
    assertIntersection(1,    1,  0.6f, 0, -1, 0, 1);
}