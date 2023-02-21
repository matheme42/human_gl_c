#include "application.hpp"


Application::Application(){
    init();
    program.Load(vertexSrc, fragSrc);
	initCube();
}


void Application::initCube() {
	const GLfloat cube_strip[] = {
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_strip), cube_strip, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
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
	mat4 P, M, R, V;

	float ok = 10.0f;
	P = perspective(60, (float)WINDOWS_X / (float)WINDOWS_Y, 0.1f, 100.0f);
	M = translate(vec3({0, 0, -2.0f}));

//	std::cout << lookAt(vec3({0, 0, 0}), vec3({0, 1, 0}), vec3({0, 1, 0})) << std::endl;
	V = lookAt(vec3({0, 2, -10}), vec3({0, -0.2f, 1}), vec3({0, 1, 0}));
    program.Activate();
//	program.setMat4("matrice", P * M);
	glBindVertexArray(cube);
	glfwSwapInterval(0);
	while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
	{
		R = rotate(mat4(1), 10 + ok, vec3({0, 1, 0}));
		glfwPollEvents();
		program.setMat4("matrice", P * V * M * R);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);	
		ok += 0.02f;
		glfwSwapBuffers(window);
	}
}