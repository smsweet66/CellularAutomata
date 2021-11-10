#shader vertex
#version 400 core

layout(location = 0) in vec4 position;

uniform mat4 u_proj;
uniform mat4 u_model;

out mat4 v_colorTransform;

void main()
{
    gl_Position = u_proj * u_model * position;
    v_colorTransform = u_proj;
};


#shader fragment
#version 400 core

layout(location = 0) out vec4 color;

in mat4 v_colorTransform;

uniform vec4 u_color;

void main()
{
    color = v_colorTransform * u_color;
    if(color.x < 0)
        color.x *= -1;
    if(color.y < 0)
        color.y *= -1;
};