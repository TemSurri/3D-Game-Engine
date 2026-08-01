#pragma once
#include "../../shader/shader.h"
#include "../../gl_resources/texture.h"


//this class owns a models texture and shader
class Material {

	public:
		//texture thing goes here
		Shader* shader = nullptr;
		Tex* texture = nullptr;

		//if shininess is 0 then mat is not reflective so no need to calculate the specular light
		float shininess{};
		Tex* specular_map_tex = nullptr;

};