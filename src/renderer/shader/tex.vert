#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 2) in vec2 aTex;
layout(location = 3) in vec3 aNorm;

out vec2 texCoord;


out vec3 FragPos;
out vec3 FragNormal;


uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;


void main()
{

    FragPos = vec3(model * vec4(aPosition, 1.0));
    FragNormal = aNorm;
    

    gl_Position = proj * view * model * vec4(aPosition, 1.0);
    texCoord = aTex;
    
}