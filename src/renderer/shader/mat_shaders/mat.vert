#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTex;
layout(location = 3) in vec3 aNorm;

//color
out vec3 vertexColor;
out vec2 texCoord;


uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

void main()
{
    gl_Position = proj * view * model * vec4(aPosition, 1.0);
    vertexColor = aColor;
    texCoord = aTex;
   
}