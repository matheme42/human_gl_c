#version 460

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;


uniform mat4 matrice;



void main()
{
  gl_Position =  matrice * vec4(position, 1.0f);
}
