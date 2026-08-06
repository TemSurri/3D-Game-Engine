#include "material.h"

void Material::ApplyMaterial(const Shader& shader) const {

	shader.setFloat("ambientStrength", ambience);
	
	shader.setFloat("reflectiveness", reflectiveness);

	if (shininess > 0) {
		shader.setBool("isSpecular", true);
		shader.setFloat("shininess", shininess);
	}
	
	if (diffuse > 0) {
		shader.setBool("isDiffuse", true);
		shader.setFloat("brightness", diffuse);
	}



};