#pragma once
#include "../thing/thing.h"
#include "../../shader/shader.h"

//basic properties of light: color and intensity
struct LightProperties {
	
	glm::vec3 color;
	float intensity{ 1.0f };
	float radius = 10.0f;

};

//type of lights, renderer will implement lighting depending on type
enum LightType :int {

	POINT,
	DIRECTIONAL,
	SPOT

};

// will be the main light class
class Light : public Thing {
	private:

		LightType type{};
		LightProperties properties{};

	public:
		Light(float intensity, float r, float g, float b, LightType light_type);
	
		LightProperties getProps() const {
			return properties;
		}

		LightType getType() const {
			return type;
		}

		void ApplyToShader(const Shader& shader) const;

};