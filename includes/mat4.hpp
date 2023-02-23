#ifndef MAT4_HPP
#define MAT4_HPP

#include "Matrix.hpp"

#define PI 3.14159265358979323846f

#define RADIAN_PER_DEGRE 3.14159265358979323846f / 180.0f

#define RADIAN(x) ((x) * RADIAN_PER_DEGRE)


mat4    perspective(float fov, float ratio, float near, float far);
mat4    rotation(float angle, vec3 vector);
mat4    rotate(const mat4& matrix, float angle, vec3 vector);
mat4    translate(const vec3& v);
mat4    translate(const mat4& m, const vec3& v);
mat4    scale(const vec3& v);
mat4    scale(const mat4& m, const vec3& v);
mat4    lookAt(const vec3& from, const vec3& to, const vec3& upvector);
mat4     ortho(float left, float right, float bottom, float top);
#endif
