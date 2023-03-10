#include "textdisplay.hpp"

void TextDisplay::setProjection(mat4 projection) {
    textShader.Activate();
    textShader.setMat4("projection", projection);
}

void TextDisplay::init(mat4 projection) {
    textShader.Load("shader/textVS.glsl", "shader/textFS.glsl");
    textShader.Activate();
    textShader.setMat4("projection", projection);

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    glActiveTexture(GL_TEXTURE1);
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            ivec2({(int)face->glyph->bitmap.width, (int)face->glyph->bitmap.rows}),
            ivec2({(int)face->glyph->bitmap_left, (int)face->glyph->bitmap_top}),
            (unsigned int)face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextDisplay::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color)
{
    // Activation du rendu
    textShader.Activate();
    textShader.setVec3("textColor", color[0], color[1], color[2]);
    textShader.setInt("text", 1);
    glActiveTexture(GL_TEXTURE1);
    glBindVertexArray(VAO);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    // Boucle sur tous les caract�res
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];
        GLfloat xpos = x + ch.Bearing[0] * scale;
        GLfloat ypos = y - (ch.Size[1] - ch.Bearing[1]) * scale;
        GLfloat w = ch.Size[0] * scale;
        GLfloat h = ch.Size[1] * scale;
        // Mise � jour du VBO
        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }
        };
        // Rendu du glyphe sur le rectangle
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        // Mise � jour de la m�moire du VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Rendu du rectangle
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Avancer le curseur au glyphe suivant (noter que l�avance est calcul�e en 1/64e pixels)
        x += (ch.Advance >> 6) * scale; // D�calage � droite de 6 pour obtenir la valeur en pixels
    }
    glBindVertexArray(0);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    //  glBindTexture(GL_TEXTURE_2D, 0);
}

void TextDisplay::display(const char* text)
{
    RenderText(text, 0.0f, 0.0f, 0.5f, vec3({1.0f, 1.0f, 1.0f}));
}

void TextDisplay::display(std::string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color)
{
    RenderText(text, x, y, scale, color);

}

void TextDisplay::display(const char* text, GLfloat x, GLfloat y, GLfloat scale, vec3 color)
{
    RenderText(text, x, y, scale, color);
}

void TextDisplay::display(std::string text, vec2 position, GLfloat scale, vec3 color)
{
    RenderText(text, position[0], position[1], scale, color);
}
