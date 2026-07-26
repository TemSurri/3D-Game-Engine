#include "model.h"

void Model::render() const {

	//gotta do better error checking later
	if (!(mat || mesh)) {
		
		return;
	}

	mesh->draw();

}