#include "light.h"

Light::Light(float intensity, float r, float g, float b, LightType light_type) :Thing("light", light_type)
{
	properties.color.r = r;
	properties.color.g = g;
	properties.color.b = b;
	properties.intensity = intensity;
	type = light_type;
};


