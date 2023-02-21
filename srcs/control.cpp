#include "control.hpp"

void Control::init() {
	glfwSetWindowUserPointer(window, this);
    glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
}

void Control::setVarialbe(GLFWwindow  *window, Shader *shader) {
	this->window = window;
	this->program = shader;
}

void Control::window_size_callback(GLFWwindow* window, int width, int height) {
	Control *control = (Control*)glfwGetWindowUserPointer(window);
	std::cout << width << " " << height << std::endl;
	control->program->setMat4("matrice", perspective(60, (float)width / (float)height, 0.1f, 100.0f) * translate(vec3({0, 0, -2.0f})));
	//std::cout <<  perspective(60, (float)width / (float)height, 0.1f, 100.0f) << std::endl;
}

void Control::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

void Control::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {

}

void Control::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

}