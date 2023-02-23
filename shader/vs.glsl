#version 460

layout(location = 0) in vec3 position;

uniform mat4 M;
uniform mat4 P;
uniform mat4 V;

out vec3 textCoord;

void main()
{
  gl_Position =  P * V * M * vec4(position, 1.0f);
  textCoord = vec3(position.x, position.y, -position.z) * 2 - 1;
}
