#include "mat4.hpp"


mat4    perspective(float fov, float ratio, float near, float far) {
    float   scale = 1.0f / tanf(RADIAN(fov / 2.0f));

    return mat4({
        scale / ratio, 0,      0,                               0,
        0,             scale,  0,                               0,
        0,             0,      -((far + near) / (far - near)),  -((2 * far * near) / (far - near)),
        0,             0,      -1,                              0
    });
}


mat4    rotate(const mat4& matrix, float angle, vec3 vector) {
    float c = cosf(RADIAN(angle));
    float s = sinf(RADIAN(angle));
    vector = normalize(vector);
    float x = vector[0];
    float y = vector[1];
    float z = vector[2];
    float rc = 1 - c;

    //maybe change for opengl
    mat4 rotation({ x * x * rc + c,         x * y * rc - z * s, x * z * rc + y * s, 0
                    ,y * x * rc + z * s,    y * y * rc + c,     y * z * rc - x * s, 0
                    ,x * z * rc - y * s,    y * z * rc + x * s, z * z * rc + c,     0
                    ,0,                     0,                  0,                  1 });
    return matrix * rotation;
}


mat4 translate(const vec3& v) {
    mat4 result(1);

    result[0][3] = v[0];
    result[1][3] = v[1];
    result[2][3] = v[2];
    return result;
}

mat4 translate(const mat4& m, const vec3& v) {
    mat4 result(m);

    result *= translate(v);
    return result;
}

mat4 scale(const vec3& v) {
    mat4 result(1);
    
    result[0][0] = v[0];
    result[1][1] = v[1];
    result[2][2] = v[2];
    return result;
}


mat4 scale(const mat4& m, const vec3& v) {
    return m * scale(v);
}


mat4    lookAt(const vec3& from, const vec3& to, const vec3& upvector ) {
    const vec3 forward = normalize(from - to);
    const vec3 right   = normalize(cross_product(upvector, forward));
    const vec3 up      = cross_product(forward, right);
    return mat4({
                right[0],       right[1],       right[2],   -right.dot(from),
                up[0],          up[1],          up[2],      -up.dot(from),
                forward[0],     forward[1],     forward[2], -forward.dot(from),
                0,              0,              0,          1
    });
}