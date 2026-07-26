#pragma once

#include "mesh.h"
#include "material.h"
#include "transform.h"

class Model {

	public:
		Model() {};

		Material* mat = nullptr;
		Mesh* mesh = nullptr;
		Transform transform = Transform();

		void render() const;

};