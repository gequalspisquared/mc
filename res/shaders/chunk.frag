#version 460 core

out vec4 FragColor;

uniform sampler2D texture0;

// in vec3 pos;
in vec2 uv;

void main()
{
    // FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    vec3 tex_col = texture(texture0, uv).rgb;
    FragColor = vec4(tex_col, 1.0);
    // FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}