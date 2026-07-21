#pragma once

#include "mesh.h"
#include "transform.h"

class Model {

	public:
		Model() {};


		Mesh* mesh = nullptr;
		Transform transform = Transform();

		void render(const Shader& shader) const;

};