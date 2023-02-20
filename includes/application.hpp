#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include "mat4.hpp"


class Application {

    #define WINDOWS_X 1600
    #define WINDOWS_Y 900

    #define fragSrc "shader/fs.glsl"
    #define vertexSrc "shader/vs.glsl"


    private:
        GLFWwindow  *window;
        Shader      program;
        GLuint      cube;

        void init();
        void initCube();
    public:
        Application();

        void start();
};