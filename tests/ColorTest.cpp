#include "gmock/gmock.h"
#include "Color.h"

class ColorTest : public testing::Test {
public:
    ColorTest() {}

    void assertColor(double r, double g, double b) {
        ASSERT_DOUBLE_EQ(r, color.r());
        ASSERT_DOUBLE_EQ(g, color.g());
        ASSERT_DOUBLE_EQ(b, color.b());
    }

    Color color;
};

class ColorScalarTest : public ColorTest {};

TEST_F(ColorTest, DefaultConstructor) {
    assertColor(0, 0, 0);
}

TEST_F(ColorTest, VectorCostructor) {
    glm::vec3 vec(0.1, 0.5, 0.9);
    color = Color(vec);
    assertColor(0.1, 0.5, 0.9);
}

TEST_F(ColorTest, ValuesConstructor) {
    color = Color(0.1, 0.5, 0.9);
    assertColor(0.1, 0.5, 0.9);
}

TEST_F(ColorTest, Plus) {
    color = Color(0.1, 0.2, 0.3) + Color(0.4, 0.5, 0.6);
    assertColor(0.5, 0.7, 0.9);
}

TEST_F(ColorTest, PlusAssign) {
    color = Color(0.1, 0.2, 0.3);
    color += Color(0.4, 0.5, 0.6);
    assertColor(0.5, 0.7, 0.9);
}

TEST_F(ColorTest, Minus) {
    color = Color(0.4, 0.7, 1) - Color(0.1, 0.2, 0.3);
    assertColor(0.3, 0.5, 0.7);
}

TEST_F(ColorTest, MinusAssign) {
    color = Color(0.4, 0.7, 1);
    color -= Color(0.1, 0.2, 0.3);
    assertColor(0.3, 0.5, 0.7);
}

TEST_F(ColorTest, Multiply) {
    color = Color(0, 0.5, 1) * Color(0.6, 0.6, 0.6);
    assertColor(0, 0.3, 0.6);
}

TEST_F(ColorTest, MultiplyAssign) {
    color = Color(0, 0.5, 1);
    color *= Color(0.6, 0.6, 0.6);
    assertColor(0, 0.3, 0.6);
}

TEST_F(ColorTest, Devide) {
    color = Color(0, 0.1, 0.6) / Color(0.6, 0.1, 1);
    assertColor(0, 1, 0.6);
}

TEST_F(ColorTest, DevideAssign) {
    color = Color(0, 0.1, 0.6);
    color /= Color(0.6, 0.1, 1);
    assertColor(0, 1, 0.6);
}

TEST_F(ColorScalarTest, Plus) {
    color = Color(0.1, 0.2, 0.3) + 0.4;
    assertColor(0.5, 0.6, 0.7);
}

TEST_F(ColorScalarTest, PlusAssign) {
    color = Color(0.1, 0.2, 0.3);
    color += 0.4;
    assertColor(0.5, 0.6, 0.7);
}

TEST_F(ColorScalarTest, Minus) {
    color = Color(0.4, 0.7, 1) - 0.4;
    assertColor(0, 0.3, 0.6);
}

TEST_F(ColorScalarTest, MinusAssign) {
    color = Color(0.4, 0.7, 1);
    color -= 0.4;
    assertColor(0, 0.3, 0.6);
}

TEST_F(ColorScalarTest, Multiply) {
    color = Color(0, 0.5, 1) * 0.6;
    assertColor(0, 0.3, 0.6);
}

TEST_F(ColorScalarTest, MultiplyAssign) {
    color = Color(0, 0.5, 1);
    color *= 0.6;
    assertColor(0, 0.3, 0.6);
}

TEST_F(ColorScalarTest, Devide) {
    color = Color(0, 0.1, 0.05) / 0.1;
    assertColor(0, 1, 0.5);
}

TEST_F(ColorScalarTest, DevideAssign) {
    color = Color(0, 0.1, 0.05);
    color /= 0.1;
    assertColor(0, 1, 0.5);
}

TEST_F(ColorTest, Conversation) {
    unsigned r = Color(1, 0, 0);
    unsigned g = Color(0, 1, 0);
    unsigned b = Color(0, 0, 1);
    unsigned mix = Color(0.8, 0.2, 0.4);
    ASSERT_EQ(16711680, r);
    ASSERT_EQ(65280, g);
    ASSERT_EQ(255, b);
    ASSERT_EQ(13382502, mix);
}

TEST_F(ColorTest, IntegerConstructor) {
    color = Color(16711680);
    assertColor(1, 0, 0);
    color = Color(65280);
    assertColor(0, 1, 0);
    color = Color(255);
    assertColor(0, 0, 1);
}

TEST_F(ColorTest, Clamp) {
    color = Color(0.3, 1.6, 3);
    color.clamp();
    assertColor(0.3, 1, 1);
}