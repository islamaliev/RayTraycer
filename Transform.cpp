// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

mat3 Transform::rotate(const float degrees, const vec3& axis) {
  mat3 m(1.0f);

  vec3 normVec = glm::normalize(axis);

  float radians = (float) (degrees * M_PI / 180);
  float vx = normVec.x;
  float vy = normVec.y;
  float vz = normVec.z;
  float cosVal = cosf(radians);
  float sinVal = sinf(radians);
  float cosOp = 1 - cosVal;
  float vzSin = vz * sinVal;
  float vySin = vy * sinVal;
  float vxSin = vx * sinVal;
  m[0][0] = vx * vx * cosOp + cosVal;
  m[0][1] = vx * vy * cosOp + vzSin;
  m[0][2] = vx * vz * cosOp - vySin;
  m[1][0] = vx * vy * cosOp - vzSin;
  m[1][1] = vy * vy * cosOp + cosVal;
  m[1][2] = vy * vz * cosOp + vxSin;
  m[2][0] = vx * vz * cosOp + vySin;
  m[2][1] = vy * vz * cosOp - vxSin;
  m[2][2] = vz * vz * cosOp + cosVal;

  return m;
}

void Transform::left(float degrees, vec3& eye, vec3& up) {
  mat3 m = rotate(degrees, up);
  eye = m * eye;
  up = m * up;
}

void Transform::up(float degrees, vec3& eye, vec3& up) {
  vec3 v = glm::cross(eye, up);
  mat3 m = rotate(degrees, v);
  eye = m * eye;
  up = m * up;
}

mat4 Transform::lookAt(const vec3& eye, const vec3 &center, const vec3& up) {
  vec3 z_axis = glm::normalize(eye - center);
  vec3 x_axis = glm::normalize(glm::cross(up, z_axis));
  vec3 y_axis = glm::cross(z_axis, x_axis);

  mat4 m(
          x_axis.x, y_axis.x, z_axis.x, 0,
          x_axis.y, y_axis.y, z_axis.y, 0,
          x_axis.z, y_axis.z, z_axis.z, 0,
          -glm::dot(x_axis, eye), -glm::dot(y_axis, eye), -glm::dot(z_axis, eye), 1
  );

  return m;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  mat4 matrix(1.f);
  float zoomY = 1 / tanf(fovy * (float) M_PI / 360);
  float zoomX = zoomY / aspect;
  float z = (zNear + zFar) / (zNear - zFar);
  float zt = (2 * zNear * zFar) / (zNear - zFar);
  matrix[0][0] = zoomX;
  matrix[1][1] = zoomY;
  matrix[2][2] = z;
  matrix[3][2] = zt;
  matrix[2][3] = -1;
  matrix[3][3] = 0;
  return matrix;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
  mat4 matrix(1.0f);
  matrix[0][0] = sx;
  matrix[1][1] = sy;
  matrix[2][2] = sz;
  return matrix;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
  mat4 matrix;
  matrix[3][0] = tx;
  matrix[3][1] = ty;
  matrix[3][2] = tz;
  return matrix;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
  vec3 x = glm::cross(up,zvec); 
  vec3 y = glm::cross(zvec,x); 
  vec3 ret = glm::normalize(y); 
  return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
