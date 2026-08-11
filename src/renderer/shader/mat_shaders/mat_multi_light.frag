#version 330 core

in vec3 vertexColor;
in vec2 texCoord;
in vec3 FragNorm;
in vec3 FragPos;

out vec4 fragColor;

uniform bool isTextured;
uniform bool isSpecularMap;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform vec2 textureTiling;

uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;
uniform float specularPower;

uniform vec3 camPos;

#define MAX_LIGHTS 16

uniform int light_count;

struct Light
{
    int type;

    vec3 pos;
    vec3 dir;

    float intensity;
    float radius;

    vec3 color;

    float innerCutoff;
    float outerCutoff;
};

uniform Light lights[MAX_LIGHTS];

struct LightingResult
{
    vec3 surface;
    vec3 specular;
};

LightingResult get_lighting(Light l)
{
    vec3 lightDir;

    if (l.type == 0 || l.type == 2)
    {
        lightDir = normalize(l.pos - FragPos);
    }
    else
    {
        lightDir = normalize(-l.dir);
    }

    vec3 normal = normalize(FragNorm);
    vec3 viewDir = normalize(camPos - FragPos);

    float diffuseFactor =
        max(dot(normal, lightDir), 0.0);

    float specularFactor = 0.0;

    if (specularPower > 0.0 && diffuseFactor > 0.0)
    {
        vec3 reflectDir =
            reflect(-lightDir, normal);

        specularFactor = pow(
            max(dot(viewDir, reflectDir), 0.0),
            specularPower
        );
    }

    vec3 ambient =
        ambientStrength * l.color;

    vec3 diffuse =
        diffuseFactor *
        diffuseStrength *
        l.color;

    vec3 specular =
        specularFactor *
        specularStrength *
        l.color;

    if (isSpecularMap)
    {
        float gradient =
            texture(
                tex1,
                texCoord * textureTiling
            ).r;

        specular *= gradient;

        
        //diffuse *= gradient;
    }

    if (l.type == 2)





    {
        float theta = dot(
            normalize(FragPos - l.pos),
            normalize(l.dir)
        );

        float epsilon =
            max(
                l.innerCutoff - l.outerCutoff,
                0.0001
            );

        float spotIntensity = clamp(
            (theta - l.outerCutoff) / epsilon,
            0.0,
            1.0
        );

        spotIntensity =
            spotIntensity *
            spotIntensity *
            (3.0 - 2.0 * spotIntensity);

        diffuse *= spotIntensity;
        specular *= spotIntensity;
    }

    if (l.type != 1)
    {
        float distanceToLight =
            length(l.pos - FragPos);

        float safeRadius =
            max(l.radius, 0.0001);

        float attenuation =
            1.0 /
            (
                1.0 +
                distanceToLight * distanceToLight /
                (safeRadius * safeRadius)
            );

        diffuse *= attenuation;
        specular *= attenuation;
    }

    LightingResult result;

    result.surface =
        ambient +
        diffuse * l.intensity;

    result.specular =
        specular * l.intensity;

    return result;
}

void main()
{
    vec4 baseColor =
        vec4(vertexColor, 1.0);

    if (isTextured)
    {
        baseColor =
            texture(
                tex0,
                texCoord * textureTiling
            );
    }

    vec3 totalSurface = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    for (int i = 0; i < light_count; i++)
    {
        LightingResult lighting =
            get_lighting(lights[i]);

        totalSurface += lighting.surface;
        totalSpecular += lighting.specular;
    }

    vec3 finalColor =
        baseColor.rgb * totalSurface
        + totalSpecular;

    fragColor =
        vec4(finalColor, baseColor.a);
}