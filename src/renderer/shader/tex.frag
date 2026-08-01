#version 330 core

in vec2 texCoord;

in vec3 FragPos;
in vec3 FragNormal;

uniform sampler2D tex0;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 camPos;

out vec4 FragColor;

void main()
{
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 normal = normalize(FragNormal);
    vec3 viewDir = normalize(camPos - FragPos);

    vec3 reflectDir = reflect(-lightDir, normal);

    float specularStrength = pow(
        max(dot(viewDir, reflectDir), 0.0),
        32.0
    );

    float diffuseStrength = max(dot(normal, lightDir), 0.0);

    vec3 ambient = 0.15 * lightColor;
    vec3 diffuse = diffuseStrength * lightColor;
    vec3 specular = specularStrength * lightColor;

    vec3 lighting = ambient + diffuse + specular;

    FragColor = texture(tex0, texCoord) * vec4(lighting, 1.0);
}