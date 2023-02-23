#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "shader.hpp"
#include "mat4.hpp"
#include "skeleton.hpp"
#include "animation.hpp"

class Object {
    #define fragSrc "shader/fs.glsl"
    #define vertexSrc "shader/vs.glsl"

    Shader      program;
    GLuint      cube;
    Skeleton    skeleton;
    Animation<BONE_NUMDER> anim;

    public:
        void init(mat4 perspective, mat4 lookAt);
        void draw();
        
        void setView(mat4 lookAt4);
        void setPerspective(mat4 perspective4);
};

#endif