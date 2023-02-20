#version 460

layout(location = 0) in vec3 position;

uniform mat4 matrice;
out vec3 pos;

void main()
{
  gl_Position =  matrice * vec4(position, 1.0f);
  pos = position;
}
