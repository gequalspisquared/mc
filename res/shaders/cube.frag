#version 460 core
out vec4 FragColor;

in vec3 pos;

void main()
{
    // FragColor = vec4(0.22f, 0.58f, 0.20f, 1.0f);
    float x = (pos.x + 1.0) / 2.0;
    float y = (pos.y + 1.0) / 2.0;
    float z = (pos.z + 1.0) / 2.0;
    FragColor = vec4(x, y, z, 1.0f);
}