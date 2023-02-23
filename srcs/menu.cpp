#include "menu.hpp"

void Menu::init(float width, float height) {
    this->width = width;
    this->height = height;
    this->projection = ortho(0.0f, (float)width , 0.0f, (float)height);
    this->handCursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);

    program.Load(buttonVertexSrc, buttonFragSrc);

    text.init(this->projection);
    initButton();
}

void Menu::resize(float width, float height){
    this->width = width;
    this->height = height;
    this->projection = ortho(0.0f, (float)width , 0.0f, (float)height);

    text.setProjection(this->projection);
}


void Menu::onCursorClick(int button, int action) {
     if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if (buttonOver != "") {
            onButtonClick(buttonOver);
        }
     }
}

void Menu::onCursorChange(GLFWwindow  *window, float x, float y) {
    float butonSizeWidth = width * 0.25;

    if (x > width * 0.5f - butonSizeWidth * 0.5f && x < width * 0.5f + butonSizeWidth * 0.5f) {

        if (y > height / 10.0f - 35.0f && y <  height / 10.0f + 35.0f) {
            glfwSetCursor(window, handCursor);
            buttonOver = "Idle";
            return ;
        }
        if (y > height / 5.0f + height / 10.0f - 35.0f && y < height / 5.0f + height / 10.0f + 35.0f) {
            glfwSetCursor(window, handCursor);
            buttonOver = "Jump";
            return ;
        }

        if (y > 2 * height / 5.0f + height / 10.0f - 35.0f && y < 2 * height / 5.0f + height / 10.0f + 35.0f) {
            glfwSetCursor(window, handCursor);
            buttonOver = "Flip";
            return ;
        }

        if (y > 3 * height / 5.0f + height / 10.0f - 35.0f && y < 3 * height / 5.0f + height / 10.0f + 35.0f) {
            glfwSetCursor(window, handCursor);
            buttonOver = "Walk";
            return ;
        }

        if (y > 4 * height / 5.0f + height / 10.0f - 35.0f && y < 4 * height / 5.0f + height / 10.0f + 35.0f) {
            glfwSetCursor(window, handCursor);
            buttonOver = "OnWave";
            return ;
        }
    
    
        glfwSetCursor(window, NULL);
        buttonOver = "";
        return ;
    }
    glfwSetCursor(window, NULL);
    buttonOver = "";
}


void Menu::draw() {
    if (!enable) return ;
    drawBlur();
    float butonSizeWidth = width * 0.25;
    drawButton(vec2({butonSizeWidth, 70.0f}), vec2({width * 0.5f - butonSizeWidth * 0.5f, height / 10.0f - 35.0f}), vec4({0.7f, 0.7f, 0.7f, 1.0f}), "Idle");
    drawButton(vec2({butonSizeWidth, 70.0f}), vec2({width * 0.5f - butonSizeWidth * 0.5f, height / 5.0f + height / 10.0f - 35.0f}), vec4({0.7f, 0.7f, 0.7f, 1.0f}), "Walk");
    drawButton(vec2({butonSizeWidth, 70.0f}), vec2({width * 0.5f - butonSizeWidth * 0.5f, 2.0f * height / 5.0f + height / 10.0f - 35.0f}), vec4({0.7f, 0.7f, 0.7f, 1.0f}), "Jump");
    drawButton(vec2({butonSizeWidth, 70.0f}), vec2({width * 0.5f - butonSizeWidth * 0.5f, 3.0f * height / 5.0f + height / 10.0f - 35.0f}), vec4({0.7f, 0.7f, 0.7f, 1.0f}), "Walk");
    drawButton(vec2({butonSizeWidth, 70.0f}), vec2({width * 0.5f - butonSizeWidth * 0.5f, 4.0f * height / 5.0f + height / 10.0f - 35.0f}), vec4({0.7f, 0.7f, 0.7f, 1.0f}), "Jump");


    text.display("Idle", 0.0f, 0.78f, 0.001f, vec3({1.0, 1.0f, 1.0f}));
    text.display("Jump", -0.03f, 0.38f, 0.001f, vec3({1.0, 1.0f, 1.0f}));
    text.display("Flip", 0.0f, 0.0f, 0.001f, vec3({1.0, 1.0f, 1.0f}));
    text.display("Walk", -0.03f, -0.42f, 0.001f, vec3({1.0, 1.0f, 1.0f}));
    text.display("OnWave", -0.06f, -0.82f, 0.001f, vec3({1.0, 1.0f, 1.0f}));

}


void Menu::drawBlur() {
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBindVertexArray(button);
    program.Activate();
    
    program.setVec4("color", vec4({0.0f, 0.0f, 0.0f, 0.3f}));
    program.setMat4("M", mat4(1));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}


void Menu::drawButton(vec2 size, vec2 pos, vec4 color, std::string textString) {
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBindVertexArray(button);
    program.Activate();
    program.setVec4("color", color);
    pos[0] += size[0] * 0.5;
    pos[1] += size[1] * 0.5;
    program.setMat4("M", translate(vec3({-1.0f + (pos[0] * 2) / this->width, 1.0f - (pos[1] * 2) / this->height, 0.0f})) * scale(mat4(1), vec3({size[0] / this->width, size[1] / this->height, 0.0f})));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}


void Menu::initButton() {
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
    };

    glGenVertexArrays(1, &button);
    glBindVertexArray(button);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glBindVertexArray(0);
}