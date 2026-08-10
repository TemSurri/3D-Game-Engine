#version 330 core

in vec3 vertexColor;
in vec2 texCoord;
in vec3 FragPos;
in vec3 FragNorm;

out vec4 FragColor;

uniform bool isTextured;
uniform bool isSpecularMap;
uniform sampler2D tex0;
uniform sampler2D tex1;

uniform vec2 textureTiling;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float radius;
uniform vec3 camPos;


uniform float lightStrength;

uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;
uniform float specularPower;

uniform bool isPointLight;
uniform bool isDirectionalLight;
uniform bool isSpotLight;

uniform vec3 lightDirection;


uniform float innerCutoff;
uniform float outerCutoff;

void main()
{
    vec4 baseColor = vec4(vertexColor, 1.0);

    if (isTextured)
    {
        baseColor = texture(tex0, texCoord * textureTiling);
    }

    vec3 lightDir;

    if (isPointLight || isSpotLight)
    {
        lightDir = normalize(lightPos - FragPos);
    }
    else if (isDirectionalLight)
    {
        lightDir = normalize(-lightDirection);
    }

    vec3 normal = normalize(FragNorm);
    vec3 viewDir = normalize(camPos - FragPos);

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


    if (isSpecularMap)
    {
        float color = texture(tex1, texCoord * textureTiling).r;
        specular *= color;
    }

    if (isSpotLight) {
        float theta = dot(
            normalize(FragPos - lightPos),
            normalize(lightDirection)
        );

        float epsilon = max(innerCutoff - outerCutoff, 0.0001);

        float spotIntensity = clamp(
            (theta - outerCutoff) / epsilon,
            0.0,
            1.0
        );

        spotIntensity =
            spotIntensity * spotIntensity * (3.0 - 2.0 * spotIntensity);


        diffuse *= spotIntensity;
        specular *= spotIntensity;

    }


    if (!isDirectionalLight) {

        //calculating and applying distance attenutation

        float distanceToLight = length(lightPos - FragPos);

        float attenuation =
            1.0 /
            (1.0 + distanceToLight * distanceToLight / (radius * radius));

        diffuse *= attenuation;
        specular *= attenuation;

    }

    // Same visual behavior as your original shader
    vec3 finalColor =
        baseColor.rgb * (ambient + diffuse * lightStrength)
        + specular * lightStrength;

    FragColor =
        vec4(finalColor, baseColor.a);
}