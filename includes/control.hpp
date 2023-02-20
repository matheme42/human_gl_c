#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "mat4.hpp"
#include <GLFW/glfw3.h>

class Control {
    GLFWwindow  *window;
    
    public:
        vec3 look;
        vec3 position;

    void init();
};

#endif