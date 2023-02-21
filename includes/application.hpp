#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include "mat4.hpp"
#include "control.hpp"
#include "object.hpp"

class Application {

    #define WINDOWS_X 1600
    #define WINDOWS_Y 900

    #define fragSrc "shader/fs.glsl"
    #define vertexSrc "shader/vs.glsl"


    private:
        GLFWwindow  *window;
        Control     control;
        Shader      program;
        Object      object;

        void init();
        void initCube();
    public:
        Application();

        void start();
};

#endif