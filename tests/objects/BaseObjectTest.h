#pragma once


#include "gmock/gmock.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Object.h"
#include "Ray.h"

using namespace testing;

const float DELTA = 0.02f;

class BaseObjectTest : public testing::Test {
public:
    BaseObjectTest()
        : object(nullptr)
        , matrix(1.f) {}

    virtual Object* createObject() = 0;

    void SetUp() override {
        createNewObjectWithCurrentTransform();
        transforms.clear();
    }

    void setNewObject(Object* object) {
        if (this->object) {
            delete this->object;
        }
        this->object = object;
        transforms.clear();
    }

    void createNewObjectWithCurrentTransform() {
        if (object) {
            delete object;
        }
        object = createObject();
    }

    void TearDown() override {
        delete object;
    }

    void translate(float x, float y, float z) {
        const glm::mat4& m = glm::translate(glm::mat4(1), glm::vec3(x, y, z));
        matrix = m * object->getTransform();
        createNewObjectWithCurrentTransform();
        std::stringstream s;
        s << "translate(" << x << ", " << y << ", " << z << ")";
        transforms.push_back(s.str());
    }

    void rotate(float degree, float x, float y, float z) {
        const glm::mat4& m = glm::rotate(glm::mat4(1), (double) degree, glm::vec3(x, y, z));
        matrix = m * object->getTransform();
        createNewObjectWithCurrentTransform();
        std::stringstream s;
        s << "rotate(" << degree << "˚, " << x << ", " << y << ", " << z << ")";
        transforms.push_back(s.str());
    }

    void scale(float x, float y, float z) {
        const glm::mat4& m = glm::scale(glm::mat4(1), glm::vec3(x, y, z));
        matrix = m * object->getTransform();
        createNewObjectWithCurrentTransform();
        std::stringstream s;
        s << "scale(" << x << ", " << y << ", " << z << ")";
        transforms.push_back(s.str());
    }

    void assertIntersection(float rayX, float rayY, float rayZ, float dirX, float dirY, float dirZ, float dist) {
        Ray* ray = new Ray();
        ray->pos = glm::vec4(rayX, rayY, rayZ, 1);
        ray->dir = glm::vec4(dirX, dirY, dirZ, 0);
        double actDist = object->intersect(ray);
        EXPECT_TRUE(IntersectionMatch(ray, dist, actDist));
    }

    glm::vec3 getNormal() {
        return getNormal(0, 0, 1);
    }

    glm::vec3 getNormal(float x, float y, float z) {
        glm::vec4 point(x, y, z, 1);
        return object->getNormal(point);
    }

    void assertNormal(float x, float y, float z) {
        glm::vec3 n = getNormal();
        EXPECT_TRUE(NormalMatch(x, y, z, n.x, n.y, n.z));
    }

    void assertNormal(float x1, float y1, float z1, float x2, float y2, float z2) {
        glm::vec3 n = getNormal(x1, y1, z1);
        EXPECT_TRUE(NormalMatch(x1, y1, z1, n.x, n.y, n.z, x2, y2, z2));
    }

    Object* object;

protected:
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

    const glm::mat4& getTransform() {
        return matrix;
    }

private:
    ::testing::AssertionResult IntersectionMatch(Ray* ray, float expDist, float actDist) {
        if (fabsf(expDist - actDist) > DELTA) {
            const glm::vec4& p = ray->pos;
            const glm::vec4& d = ray->dir;
            return ::testing::AssertionFailure() << "ray(" << p.x << ", " << p.y << ", " << p.z << ") -> ("
                    << d.x << ", " << d.y << ", " << d.z << "), expected distanse: " << expDist
                    << ", actual: " << actDist;
        }
        return ::testing::AssertionSuccess();
    }

    ::testing::AssertionResult NormalMatch(float px, float py, float pz, float x1, float y1, float z1, float x2, float y2, float z2) {
        if (fabsf(x1 - x2) > DELTA || fabsf(y1 - y2) > DELTA || fabsf(z1 - z2) > DELTA) {
            return ::testing::AssertionFailure() << "point(" << px << ", " << py << ", " << pz
                    << ") -> expected(" << x2 << ", " << y2 << ", " << z2
                    << ") != actual(" << x1 << ", " << y1 << ", " << z1 << ")" << getTranslations();
        }

        return ::testing::AssertionSuccess();
    }

    ::testing::AssertionResult NormalMatch(float x1, float y1, float z1, float x2, float y2, float z2) {
        if (fabsf(x1 - x2) > DELTA || fabsf(y1 - y2) > DELTA || fabsf(z1 - z2) > DELTA) {
            return ::testing::AssertionFailure() << "expected(" << x1 << ", " << y1 << ", " << z1
                    << ") != actual(" << x2 << ", " << y2 << ", " << z2 << ")";
        }

        return ::testing::AssertionSuccess();
    }

    glm::mat4 matrix;
    std::vector<std::string> transforms;
};
