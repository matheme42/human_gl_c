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
#include "cubemap.hpp"

class Application {

    #define WINDOWS_X 1600
    #define WINDOWS_Y 900

    private:
        GLFWwindow  *window;
        Control     control;
        Object      object;
        CubeMap     cubemap;

        void init();
        void configure();
        void start();
    public:
        Application();
};

#endif