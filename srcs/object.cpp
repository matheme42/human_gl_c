#include "object.hpp"

void Object::init(Shader *program) {
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
    this->program = program;


	glGenVertexArrays(1, &cube);
    glBindVertexArray(cube);

	GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_strip), cube_strip, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindVertexArray(0);

    program->Activate();
    program->setMat4("M", translate(vec3({0, 0, 5.0f})) * rotate(mat4(1), rot, vec3({0, 1, 0})));
}

void Object::rotation() {
    rot += 0.02f;
    program->Activate();
    program->setMat4("M", translate(vec3({0, 0, 5.0f})) * rotate(mat4(1), rot, vec3({0, 1, 0})));
}


void Object::draw() {
    program->Activate();
    glBindVertexArray(cube);

    for (unsigned n = 0; n < BONE_NUMDER; n++) {
        program->setMat4("M",  translate(vec3({0, 0, 5.0f})) * rotate(mat4(1), rot, vec3({0, 1, 0})) * skeleton.GetBone(n).offsetM);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);	
    }
}