#version 460 core

out vec4 FragColor;

in vec3 pos;

void main()
{
    // FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    FragColor = vec4(pos, 1.0);
}