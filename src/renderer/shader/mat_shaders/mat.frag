#version 330 core

//inputs from the vert

in vec3 vertexColor;
in vec2 texCoord;

//final color output

out vec4 FragColor;

// uniforms ------------------------

//flow control uniforms 

uniform bool isTextured;


//usage unifroms

uniform sampler2D tex0;

void main()
{
    FragColor = vec4(vertexColor, 1.0);

    if (isTextured) {
        FragColor = texture(tex0, texCoord);
    }
    
}