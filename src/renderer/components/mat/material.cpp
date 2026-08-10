#include "material.h"

void Material::ApplyMaterial(const Shader& shader) const {

	shader.setFloat("ambientStrength", ambience);	
		
	shader.setFloat("specularPower", specPower);
	
	shader.setFloat("specularStrength", specStrength);
		
	shader.setFloat("diffuseStrength", diffuse);
	
	shader.setVec2("textureTiling", tiling);


};