#pragma once
#include "../../shader/shader.h"
#include "../../gl_resources/texture.h"


//this class owns a models texture and shader
class Material {

	public:
		//texture thing goes here
		Shader* shader = nullptr;
		Tex* texture = nullptr;


};