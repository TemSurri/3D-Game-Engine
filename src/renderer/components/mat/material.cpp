#include "material.h"

void Material::ApplyMaterial(const Shader& shader) const {

	shader.setFloat("ambientStrength", ambience);	
		
	shader.setFloat("specularPower", specPower);
	
	shader.setFloat("specularStrength", specStrength);
		
	shader.setFloat("diffuseStrength", diffuse);
	
	shader.setVec2("textureTiling", tiling);

};

void Material::Bind(const Shader& shader) const {

    ApplyMaterial(shader);

    shader.setBool("isTextured", texture != nullptr);
    shader.setBool("isSpecularMap", specular_map_tex != nullptr);

    if (texture)
    {
        glActiveTexture(GL_TEXTURE0);
        texture->Bind();
        shader.setTex("tex0", 0);
    }

    if (specular_map_tex)
    {
        glActiveTexture(GL_TEXTURE1);
        specular_map_tex->Bind();
        shader.setTex("tex1", 1);
    }

}