#ifndef CUBEMAP_HPP
#define CUBEMAP_HPP
#define STB_IMAGE_IMPLEMENTATION

#include "shader.hpp"
#include "mat4.hpp"
#include "stb_image.h"

class CubeMap {
    private:
        Shader program;
        GLuint cubeMapTextureId;


    public:
        CubeMap();
        void initSkybox();
        void gen();
        void loadTexture(const char **fileNames);
};

#endif