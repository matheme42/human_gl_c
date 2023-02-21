#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "shader.hpp"
#include "mat4.hpp"
#include "skeleton.hpp"

class Object {
    Shader  *program;
    GLuint  cube;
    Skeleton    skeleton;
    float   rot = 0.0f;

    public:
        void init(Shader *program);
        void draw();
        void rotation();
};

#endif