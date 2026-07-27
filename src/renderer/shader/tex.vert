#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 2) in vec2 aTex;

out vec2 texCoord;


uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;


void main()
{
    gl_Position = proj * view * model * vec4(aPosition, 1.0);
    texCoord = aTex;
}