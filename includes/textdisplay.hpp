#ifndef TEXT_DISPLAY_CLASS_H
#define TEXT_DISPLAY_CLASS_H

#include "shader.hpp"
#include <map>
#include <freetype/freetype.h>
#include FT_FREETYPE_H
#include <ft2build.h>
#include "Vector.hpp"
#include "mat4.hpp"


class TextDisplay {
	struct Character {
		unsigned int textureID;  // ID handle of the glyph texture
		ivec2   Size;       // Size of glyph
		ivec2   Bearing;    // Offset from baseline to left/top of glyph
		unsigned int Advance;    // Offset to advance to next glyph
	};

	std::map<char, Character> Characters;

	GLuint VAO, VBO;
	Shader  textShader;

	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color);
	public:
		void display(const char* text);
		void display(std::string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color);
		void display(const char* text, GLfloat x, GLfloat y, GLfloat scale, vec3 color);
		void display(std::string text, vec2 position, GLfloat scale, vec3 color);
		void init(mat4 projection);
        void setProjection(mat4 projection);
};

#endif