#include "application.hpp"


Application::Application(){
    init();
    program.Load(vertexSrc, fragSrc);
}


void Application::initCube() {
	static const GLfloat cube_strip[] = {
    -0.5f, 0.5f, 0.5f,     // Front-top-left
    0.5f, 0.5f, 0.5f,      // Front-top-right
    -0.5f, -0.5f, 0.5f,    // Front-bottom-left
    0.5f, -0.5f, 0.5f,     // Front-bottom-right
    0.5f, -0.5f, -0.5f,    // Back-bottom-right
    0.5f, 0.5f, 0.5f,      // Front-top-right
    0.5f, 0.5f, -0.5f,     // Back-top-right
    -0.5f, 0.5f, 0.5f,     // Front-top-left
    -0.5f, 0.5f, -0.5f,    // Back-top-left
    -0.5f, -0.5f, 0.5f,    // Front-bottom-left
    -0.5f, -0.5f, -0.5f,   // Back-bottom-left
    0.5f, -0.5f, -0.5f,    // Back-bottom-right
    -0.5f, 0.5f, -0.5f,    // Back-top-left
    0.5f, 0.5f, -0.5f      // Back-top-right
	};


	glGenVertexArrays(1, &cube);
    glBindVertexArray(cube);

	GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_strip), &cube_strip, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 14, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);
    glBindVertexArray(0);
}

void Application::init() {
    char buff[400];
    
    getcwd(buff, sizeof(buff));
	if(!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n" );
		exit(1);
	}
	chdir(buff);
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glEnable(GL_DEPTH_TEST);



}


void Application::start() {
    program.Activate();
	glBindVertexArray(cube);
	while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);


		glfwSwapBuffers(window);
	}
}