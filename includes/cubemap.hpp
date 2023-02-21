#ifndef CUBEMAP_HPP
#define CUBEMAP_HPP

#include "shader.hpp"
#include "mat4.hpp"
#include "stb_image.h"

class CubeMap {
    private:
        Shader program;
        GLuint cubeMapTextureId;
        GLuint skybox;

    public:
        CubeMap();
        void init(mat4 perspective, mat4 lookAt);
        void genTexture();
        void loadTexture(const char **fileNames);
        void draw();
        void setView(mat4 lookAt4);
        void setPerspective(mat4 perspective4);
};

#endif