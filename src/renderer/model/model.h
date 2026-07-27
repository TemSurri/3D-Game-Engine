#pragma once

#include "mesh/mesh.h"
#include "mat/material.h"
#include "transform/transform.h"

class Model {

	public:
		Model() {};

		Material* mat = nullptr;
		Mesh* mesh = nullptr;
		Transform transform = Transform();

		void render() const;

};