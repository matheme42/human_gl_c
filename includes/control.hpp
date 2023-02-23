#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "mat4.hpp"
#include "shader.hpp"
#include "functional"
#include <GLFW/glfw3.h>

class Control {    
    public:
        vec3 look;
        vec3 position;
        bool pause = false;

    void init(GLFWwindow *window);
    void getKeyboardEvent(GLFWwindow* window);
    std::function<void(float, float)> onWindowChange;
    std::function<void(mat4)> onViewChange;
    std::function<void(bool)> onPauseChange;
    std::function<void(float, float)> onPauseCursorPosition;
    std::function<void(int, int)> onPauseCursorClick;


    private:
        static void window_size_callback(GLFWwindow* window, int width, int height);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};

#endif