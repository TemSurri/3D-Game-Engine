#pragma once
#include "../thing/thing.h"

//basic properties of light: color and intensity
struct LightProperties {
	
	glm::vec3 color;
	float intensity{ 1.0f };

};

//type of lights, renderer will implement lighting depending on type
enum LightType :int {

	POINT,
	DIRECTIONAL,

};

// will be the main light class
class Light : public Thing {
	private:

		LightType type{};
		LightProperties properties{};

	public:
		Light(float intensity, float r, float g, float b, LightType light_type);
	
		LightProperties getProps() {
			return properties;
		}

		LightType getType() {
			return type;
		}

};