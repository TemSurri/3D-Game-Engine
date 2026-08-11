#include "light.h"

Light::Light(float intensity, float r, float g, float b, LightType light_type) :Thing("light", light_type)
{
	properties.color.r = r;
	properties.color.g = g;
	properties.color.b = b;
	properties.intensity = intensity;
	type = light_type;
};

void Light::ApplyToShader(const Shader& shader) const {


	//light color
	shader.setVec3(
		"lightColor",
		{
		   properties.color
		}
	);

	shader.setFloat("lightStrength", properties.intensity);


	switch (type) {

	case DIRECTIONAL:

		shader.setBool("isDirectionalLight", true);

		shader.setFloat("radius", properties.radius);

		shader.setVec3("lightDirection", transform.rotation);

		break;

	case POINT:

		shader.setBool("isPointLight", true);

		shader.setFloat("radius", properties.radius);

		shader.setVec3(
			"lightPos",
			transform.position
		);

		break;



	case SPOT:

		shader.setBool("isSpotLight", true);

		shader.setVec3(
			"lightPos",
			transform.position
		);

		shader.setFloat("radius", properties.radius);
		shader.setVec3("lightDirection", transform.rotation);

		shader.setFloat("innerCutoff", properties.innerCutoff);
		shader.setFloat("outerCutoff", properties.outerCutoff);

		break;


	}


};