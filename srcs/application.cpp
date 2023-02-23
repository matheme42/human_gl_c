#include "application.hpp"


Application::Application(){
    init();
	configure();
	start();
}

void Application::configure() {
	mat4 perspective4 = perspective(60, (float)WINDOWS_X / (float)WINDOWS_Y, 0.1f, 100.0f);
	mat4 lookAt4 = lookAt(vec3({0, 2, -10}), vec3({0, 0, 0}), vec3({0, 1, 0}));

	control.init(window);

	control.onPerspectiveChange = ([&](mat4 perspective4){
		object.setPerspective(perspective4);
		cubemap.setPerspective(perspective4);
	});

	control.onViewChange = ([&](mat4 view) {
		object.setView(view);
		cubemap.setView(view);
	});

	object.init(perspective4, lookAt4);
	cubemap.init(perspective4, lookAt4);
}

void Application::init() {
    char buff[400];
    
	cwd(buff, sizeof(buff));
	if(!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n" );
		exit(1);
	}
	cd(buff);
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Open a window and create its OpenGL context
	window = glfwCreateWindow(WINDOWS_X, WINDOWS_Y, "Human GL", NULL, NULL);
	if(window == NULL) {
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		exit(1);
	}

    glfwMakeContextCurrent(window);
    gladLoadGL();

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
}


void Application::start() {
	glfwSwapInterval(0);
	while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		control.getKeyboardEvent(window);
		cubemap.draw();
		object.draw();
		object.rotation();
		glfwSwapBuffers(window);
	}
}
