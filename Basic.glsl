#shader vertex
#version 440 core

layout (location = 0) in vec3 aPos;
out vec4 vertexColor;
uniform mat4 uMVP;

void main()
{
    gl_Position = uMVP * vec4(aPos, 1.0);
    vertexColor = vec4(1.0, 1.0, 0.0, 1.0);
}

#shader fragment
#version 440 core

out vec4 FragColor;
in vec4 vertexColor;

void main()
{
    FragColor = vertexColor;
} 