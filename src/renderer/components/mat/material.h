#pragma once
#include "../../shader/shader.h"
#include "../../gl_resources/texture.h"


//this class owns a models texture and shader
class Material {

	public:
		//texture thing goes here
		Shader* shader = nullptr;
		Tex* texture = nullptr;

	
		// Material Lighting Properties

		//
		// ambience
		// --------
		// Minimum light the material always receives.
		// Higher values brighten surface even when they face away from the light.
		// Typical range: 0.05 - 0.30
		//
		// diffuse
		// -------
		// How strongly the material responds to direct light.
		// 0.0 = ignores direct lighting.
		// 1.0 = normal response.
		// >1.0 = exaggerated brightness.
		//
		// specularStrength
		// ----------------
		// Brightness/intensity of the specular (reflective) highlight.
		// 0.0 = matte surface.
		// Higher values = brighter reflections.
		//
		// specularPower
		// -------------
		// Concentration of the specular highlight.
		// Low values (8-16)  = wide, soft highlight.
		// Medium (32-64)     = typical shiny plastic.
		// High (128+)        = tiny, sharp highligt (polished metal).

		float specStrength{};
		float diffuse{};
		float specPower{};
		float ambience = 0.15f;
		

		Tex* specular_map_tex = nullptr;


		void ApplyMaterial(const Shader& shader) const;


};