#include "object.hpp"

Animation<BONE_NUMDER> put();
Animation<BONE_NUMDER> jump();
Animation<BONE_NUMDER> hand();
Animation<BONE_NUMDER> walking();

void Object::init(mat4 perspective, mat4 lookAt) {
	const GLfloat cube_strip[] = {
        0.0f, 1.0f, 1.0f,     // Front-top-left
        1.0f, 1.0f, 1.0f,      // Front-top-right
        0.0f, 0.0f, 1.0f,    // Front-bottom-left
        1.0f, 0.0f, 1.0f,     // Front-bottom-right
        1.0f, 0.0f, 0.0f,    // Back-bottom-right
        1.0f, 1.0f, 1.0f,      // Front-top-right
        1.0f, 1.0f, 0.0f,     // Back-top-right
        0.0f, 1.0f, 1.0f,     // Front-top-left
        0.0f, 1.0f, 0.0f,    // Back-top-left
        0.0f, 0.0f, 1.0f,    // Front-bottom-left
        0.0f, 0.0f, 0.0f,   // Back-bottom-left
        1.0f, 0.0f, 0.0f,    // Back-bottom-right
        0.0f, 1.0f, 0.0f,    // Back-top-left
        1.0f, 1.0f, 0.0f      // Back-top-right
    };
    
    program.Load(vertexSrc, fragSrc);

	glGenVertexArrays(1, &cube);
    glBindVertexArray(cube);


    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_strip), cube_strip, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glBindVertexArray(0);


    program.Activate();
    program.setMat4("P", perspective);
	program.setMat4("V", lookAt);

    anim = walking();
    anim.Loop();
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
    anim.Uptdate();
    skeleton.GetBone(HIP).ComputeAnimFinalMatrix(anim.currentFrame);
    
    program.Activate();
    glBindVertexArray(cube);
    for (unsigned n = 1; n < BONE_NUMDER; n++) {
        program.setMat4("M", skeleton.GetBone(n).ModelMatrix());
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);	
    }
}