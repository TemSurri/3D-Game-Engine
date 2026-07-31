#pragma once

#include "../mesh/mesh.h"
#include "../mat/material.h"
#include "../thing/thing.h"

class Model : public Thing {

	public:

		Model(std::string modelName, int modelId) : Thing(modelName, modelId) {

		};

		Material* mat = nullptr;
		Mesh* mesh = nullptr;

		void render() const;

};