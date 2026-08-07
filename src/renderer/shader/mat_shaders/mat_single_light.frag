#version 330 core

in vec3 vertexColor;
in vec2 texCoord;
in vec3 FragPos;
in vec3 FragNorm;

out vec4 FragColor;

uniform bool isTextured;
uniform sampler2D tex0;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float radius;
uniform vec3 camPos;


uniform float lightStrength;

uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;
uniform float specularPower;

void main()
{
    vec4 baseColor = vec4(vertexColor, 1.0);

    if (isTextured)
    {
        baseColor = texture(tex0, texCoord);
    }

    vec3 normal = normalize(FragNorm);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(camPos - FragPos);

    float distanceToLight = length(lightPos - FragPos);

    float attenuation =
        1.0 /
        (1.0 + distanceToLight * distanceToLight / (radius * radius));

    // Diffuse angle
    float diffuseFactor =
        max(dot(normal, lightDir), 0.0);

    // Specular angle
    float specularFactor = 0.0;

    if (specularPower > 0.0 && diffuseFactor > 0.0)
    {

         // Reflection direction
        vec3 reflectDir =
            reflect(-lightDir, normal);

        specularFactor = pow(
            max(dot(viewDir, reflectDir), 0.0),
            specularPower
        );
    }

    // Individual lighting components
    vec3 ambient =
        ambientStrength *
        lightColor;

    vec3 diffuse =
        diffuseFactor *
        diffuseStrength *
        lightColor;

    vec3 specular =
        specularFactor *
        specularStrength *
        lightColor;

    diffuse *= attenuation;
    specular *= attenuation;

    // Light strength controls the actual light contribution
    vec3 lighting =
        ambient +
        (diffuse + specular) * lightStrength;

    // Same visual behavior as your original shader
    vec3 finalColor =
        baseColor.rgb * lighting;

    FragColor =
        vec4(finalColor, baseColor.a);
}