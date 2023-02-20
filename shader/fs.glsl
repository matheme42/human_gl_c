#version 460

out vec4 FragColor;
in vec3 pos;

void main()
{
  FragColor = vec4(pos + 0.5, 1.0f);
}
