#include "model.h"

void Model::render(const Shader& shader) const {

    shader.setMat4(
        "model",
        transform.getModelMatrix()
    );

	mesh->draw();

}