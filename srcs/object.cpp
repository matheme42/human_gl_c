#include "object.hpp"

void Object::init(mat4 perspective, mat4 lookAt) {
	const GLfloat cube_strip[] = {
    -0.5f, 1.0f, 0.5f,     // Front-top-left
    0.5f, 1.0f, 0.5f,      // Front-top-right
    -0.5f, 0.0f, 0.5f,    // Front-bottom-left
    0.5f, 0.0f, 0.5f,     // Front-bottom-right
    0.5f, 0.0f, -0.5f,    // Back-bottom-right
    0.5f, 1.0f, 0.5f,      // Front-top-right
    0.5f, 1.0f, -0.5f,     // Back-top-right
    -0.5f, 1.0f, 0.5f,     // Front-top-left
    -0.5f, 1.0f, -0.5f,    // Back-top-left
    -0.5f, 0.0f, 0.5f,    // Front-bottom-left
    -0.5f, 0.0f, -0.5f,   // Back-bottom-left
    0.5f, 0.0f, -0.5f,    // Back-bottom-right
    -0.5f, 1.0f, -0.5f,    // Back-top-left
    0.5f, 1.0f, -0.5f      // Back-top-right
};

    program.Load(vertexSrc, fragSrc);

	glGenVertexArrays(1, &cube);
    glBindVertexArray(cube);

	GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_strip), cube_strip, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindVertexArray(0);

    program.Activate();
    program.setMat4("P", perspective);
	program.setMat4("V", lookAt);
    program.setMat4("M", translate(vec3({0, 0, 5.0f})) * rotate(mat4(1), rot, vec3({0, 1, 0})));
}

void Object::rotation() {
    rot += 0.02f;
    program.Activate();
    program.setMat4("M", translate(vec3({0, 0, 5.0f})) * rotate(mat4(1), rot, vec3({0, 1, 0})));
}

void Object::setView(mat4 lookAt4) {
    program.Activate();
    program.setMat4("V", lookAt4);
}

void Object::setPerspective(mat4 perspective4) {
    program.Activate();
    program.setMat4("P", perspective4);
}



void Object::draw() {
    program.Activate();
    glBindVertexArray(cube);

    for (unsigned n = 1; n < BONE_NUMDER; n++) {
        program.setMat4("M",  translate(vec3({0, 0, 5.0f})) * rotate(mat4(1), rot, vec3({0, 1, 0})) * skeleton.GetBone(n).ModelMatrix());
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);	
    }
}