#version 330 core

in vec2 texCoord;

in vec3 FragPos;
in vec3 FragNormal;

uniform sampler2D tex0;

uniform vec3 lightPos;
uniform vec3 lightColor;

out vec4 FragColor;

void main()
{

    FragColor = texture(tex0, texCoord) * vec4(
        (0.15 * lightColor) + (max(dot(normalize(FragNormal), normalize(lightPos - FragPos)), 0.0) * lightColor),
        1.0
    );
}