#include "cubemap.hpp"


CubeMap::CubeMap() {}

void CubeMap::genTexture() {
    glActiveTexture(GL_TEXTURE0 + 0);
    glGenTextures(1, &cubeMapTextureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureId);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}


void CubeMap::loadTexture(const char **fileNames) {
    void* data;
    int x, y, comp;

    stbi_set_flip_vertically_on_load(false);
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureId);
    for (int n = 0; n < 6; n++) {
        if (!(data = stbi_load(fileNames[n], &x, &y, &comp, 0))) {
            std::cerr << "Failed to load" << fileNames[n] << std::endl;
            continue;
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + n, 0, GL_RGB, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
}


void CubeMap::init(mat4 perspective, mat4 lookAt) {
    const char** texturesName;

    float skyboxVertices[] =
    {
        //   Coordinates
        -1.0f, -1.0f,  1.0f,//        7--------6
        1.0f, -1.0f,  1.0f,//       /|       /|
        1.0f, -1.0f, -1.0f,//      4--------5 |
        -1.0f, -1.0f, -1.0f,//      | |      | |
        -1.0f,  1.0f,  1.0f,//      | 3------|-2
        1.0f,  1.0f,  1.0f,//      |/       |/
        1.0f,  1.0f, -1.0f,//      0--------1
        -1.0f,  1.0f, -1.0f
    };

    float texturesUv[] =
    {
        //   Coordinates
        0.0f,0.0f,
        0.0f,1.0f,
        0.0f,0.0f,
        0.0f,1.0f,
        1.0f,0.0f,
        1.0f,1.0f,
        1.0f,0.0f,
        1.0f,1.0f
    };

    unsigned int skyboxIndices[] =
    {
        // Right
        1, 2, 6,
        6, 5, 1,
        // Left
        0, 4, 7,
        7, 3, 0,
        // Top
        4, 5, 6,
        6, 7, 4,
        // Bottom
        0, 3, 2,
        2, 1, 0,
        // Back
        0, 1, 5,
        5, 4, 0,
        // Front
        3, 7, 6,
        6, 2, 3
    };

    std::vector <GLuint> indices(skyboxIndices, skyboxIndices + sizeof(skyboxIndices) / sizeof(GLuint));

    texturesName = new const char* [6];
    texturesName[0] = "textures/skybox/X+.png";
    texturesName[1] = "textures/skybox/X-.png";
    texturesName[2] = "textures/skybox/Y+.png";
    texturesName[3] = "textures/skybox/Y-.png";
    texturesName[4] = "textures/skybox/Z+.png";
    texturesName[5] = "textures/skybox/Z-.png";
    genTexture();
    loadTexture(texturesName);
    delete[] texturesName;

    glGenVertexArrays(1, &skybox);

    glBindVertexArray(skybox);

    /// skyboxEBO Init
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);


    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    GLuint VBO2;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texturesUv), texturesUv, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glBindVertexArray(0);

    program.Load("shader/skyBoxVS.glsl", "shader/skyBoxFS.glsl");

    program.Activate();

    program.setInt("skybox", 0);
	program.setMat4("projection", perspective);
	program.setMat4("view", mat4(1));
}


void CubeMap::setView(mat4 lookAt4) {
    program.Activate();
    program.setMat4("view", lookAt4);
}

void CubeMap::setPerspective(mat4 perspective4) {
    program.Activate();
    program.setMat4("projection", perspective4);
}


void CubeMap::draw() {
    glDepthFunc(GL_LEQUAL);
    program.Activate();

    glBindVertexArray(skybox);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDepthFunc(GL_LESS);
}
