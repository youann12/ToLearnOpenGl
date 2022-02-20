#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 vertexPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model  * vec4(aPosition, 1.0f);
    Normal = mat3(transpose(inverse(model))) * aNormal;
    vertexPos = vec3(model * vec4(aPosition, 1.0f));
}