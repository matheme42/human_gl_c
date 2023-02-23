#ifndef MENU_HPP
#define MENU_HPP

#include "textdisplay.hpp"
#include "mat4.hpp"
#include <GLFW/glfw3.h>
#include <functional>

class Menu {
    private:
        #define buttonFragSrc "shader/buttonFS.glsl"
        #define buttonVertexSrc "shader/buttonVS.glsl"

        Shader      program;
        TextDisplay text;
        GLuint      button;
        float       width;
        float       height;
        mat4        projection;
        GLFWcursor* handCursor;
        std::string buttonOver;


    private:
        void initButton();
        void drawButton(vec2 size, vec2 pos, vec4 color, std::string text);
        void drawBlur();
    public:
        std::function<void(std::string)> onButtonClick;

        bool enable = false;
        void init(float width, float height);
        void resize(float width, float height);
        void onCursorChange(GLFWwindow  *window, float posX, float posY);
        void onCursorClick(int button, int action);
        void draw();
    
};

#endif