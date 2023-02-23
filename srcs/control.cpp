#include "control.hpp"

void Control::init(GLFWwindow *window) {
	glfwSetWindowUserPointer(window, this);
    glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	look = vec3({0, 0, 1});
    position = vec3({0, 0, -7});
}

void Control::window_size_callback(GLFWwindow* window, int width, int height) {
	static Control *control = (Control*)glfwGetWindowUserPointer(window);
	glfwGetFramebufferSize(window, &width, &height);
    control->onWindowChange(width, height);
	glViewport(0, 0, width, height);
}

void Control::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    static Control *control = (Control*)glfwGetWindowUserPointer(window);
    if (key == GLFW_KEY_LEFT_ALT) {
        if (action == GLFW_PRESS) {
            control->pause = true;
            control->onPauseChange(control->pause);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            control->pause = false;
            control->onPauseChange(control->pause);
        	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursor(window, NULL);
        }
    }
}

void Control::getKeyboardEvent(GLFWwindow* window) {
    static float previousTime = 0.0f;
    
    #define KEYBOARD_EVENT_REFRESH 1.0f / 60.0f

    float time = (float)glfwGetTime();
    float sensibility = (time - previousTime) * 4;

    if (pause) sensibility = 0;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += look * sensibility;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position += normalize(cross_product(look, vec3({0.0f, 1.0f, 0.0f}))) * -1 * sensibility;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position += look * -1 * sensibility;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += normalize(cross_product(look, vec3({0.0f, 1.0f, 0.0f}))) * sensibility;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        position[1] += 1.0f * sensibility;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        position[1] += -1.0f * sensibility;
    
    onViewChange(lookAt(position, position + look, vec3({0, 1, 0})));
    previousTime = time;
}

void Control::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	static Control *control = (Control*)glfwGetWindowUserPointer(window);
	static vec2 mousePos = vec2(0);

    if (control->pause) {
        mousePos[0] = xpos;
        mousePos[1] = ypos;
        control->onPauseCursorPosition(xpos, ypos);
        return ;
    }
	static float Pitch = -45.0f;
	static float Yaw = 10.0f;

	Pitch += (float)(ypos - mousePos[1]) * 0.1;
    Yaw += (float)(xpos - mousePos[0]) * 0.1;
    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
       Pitch = -89.0f;

    vec3 front;
    front[0] = cos(RADIAN(Yaw)) * cos(RADIAN(Pitch));
    front[1] = -sin(RADIAN(Pitch));
    front[2] = sin(RADIAN(Yaw)) * cos(RADIAN(Pitch));

    control->look = normalize(front);
    mousePos[0] = xpos;
    mousePos[1] = ypos;

    control->onViewChange(lookAt(control->position, control->position + control->look, vec3({0, 1, 0})));
}

void Control::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    static Control *control = (Control*)glfwGetWindowUserPointer(window);

    if (control->pause) {
        control->onPauseCursorClick(button, action);
        return ;
    }
}