#version 330 core

//inputs from the vert

in vec3 vertexColor;
in vec2 texCoord;
in vec3 FragPos;
in vec3 FragNorm;

//final color output

out vec4 FragColor;

//uniforms 

//flow control uniforms 

uniform bool isTextured;
uniform bool isDiffuse;
uniform bool isSpecular;

//usage unifroms

uniform sampler2D tex0;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 camPos;

uniform float lightStrength;
uniform float specularPower;

void main()
{
    vec4 baseColor = vec4(vertexColor, 1.0);

    if (isTextured)
    {
        baseColor = texture(tex0, texCoord);
    }

    vec3 lighting = ambientStrength * lightColor;

    if (isDiffuse || isSpecular)
    {
        vec3 normal = normalize(FragNorm);
        vec3 lightDir = normalize(lightPos - FragPos);

        float facingLight = max(dot(normal, lightDir), 0.0);

        if (isDiffuse)
        {
            lighting += facingLight * lightColor;
        }

        if (isSpecular && facingLight > 0.0)
        {
            vec3 viewDir = normalize(camPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, normal);

            float specularAmount =
                pow(
                    max(dot(viewDir, reflectDir), 0.0),
                    specularPower
                );

            lighting += specularAmount * lightColor;
        }
    }

    lighting *= lightStrength;

    FragColor = vec4(
        baseColor.rgb * lighting,
        baseColor.a
    );
}