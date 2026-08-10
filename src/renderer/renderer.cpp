#include "renderer.h"
#include <iostream>

void Renderer::renderModel(Model& model) {

    //ERROR HANDLE FOR THE BASIC NEEDS TO RENDER

	//no mat
	if (!(model.mat)) {
        std::cout << "model has no material" << std::endl;
		return;
	}
    // no mesh
    if (!(model.mesh)) {
        std::cout << "model has no mesh" << std::endl;
        return;
    }
	// no shader
	if (!(model.mat->shader)) {
        std::cout << "model has no shader" << std::endl;
		return;
	}
    // no camera
    if (!(current_cam)) {
        std::cout << "renderer has no cam" << std::endl;
        return;
    }

    //SET WINDOW SIZING 

    int framebufferWidth = 0;
    int framebufferHeight = 0;

    glfwGetFramebufferSize(
        window,
        &framebufferWidth,
        &framebufferHeight
    );


    //SHADER SET UP


    
    //setting up unforms ====================================================
    model.mesh->vao.Bind();
    model.mat->shader->Activate();

    //setting the projection matrix unifrom
    if (framebufferWidth > 0 && framebufferHeight > 0)
    {
        glViewport(
            0,
            0,
            framebufferWidth,
            framebufferHeight
        );

        const float aspectRatio =
            static_cast<float>(framebufferWidth) /
            static_cast<float>(framebufferHeight);

        model.mat->shader->setMat4(
            "proj",
            current_cam->getProjectionMatrix(aspectRatio)
        );
    }

    //setting the view matrix unifrom
    model.mat->shader->setMat4(
        "view", current_cam->getViewMatrix()
    );

    //setting the actual transform matrix unifrom
    model.mat->shader->setMat4(
        "model",
        model.transform.getModelMatrix()
    );
    
    //texture & draw
    // if no texture just draw 
    if (!(model.mat->texture)) {
        model.mat->shader->setBool("isTextured", false);
        model.mesh->draw();
    }
    else {

        model.mat->shader->setBool("isTextured", true);

        model.mat->texture->Bind();

        model.mat->shader->setTex("tex0", 0);

        model.mesh->draw();

        model.mat->texture->UnBind();
    }
}

void Renderer::renderModel(Model& model, Light& light) {

  
    //no mat
    if (!(model.mat)) {
        std::cout << "model has no material" << std::endl;
        return;
    }
    // no mesh
    if (!(model.mesh)) {
        std::cout << "model has no mesh" << std::endl;
        return;
    }
    // no shader
    if (!(model.mat->shader)) {
        std::cout << "model has no shader" << std::endl;
        return;
    }
    // no camera
    if (!(current_cam)) {
        std::cout << "renderer has no cam" << std::endl;
        return;
    }

    int framebufferWidth = 0;
    int framebufferHeight = 0;

    glfwGetFramebufferSize(
        window,
        &framebufferWidth,
        &framebufferHeight
    );

    //setting up unforms ====================================================
    model.mesh->vao.Bind();
    model.mat->shader->Activate();

    //setting the projection matrix unifrom
    if (framebufferWidth > 0 && framebufferHeight > 0)
    {
        glViewport(
            0,
            0,
            framebufferWidth,
            framebufferHeight
        );

        const float aspectRatio =
            static_cast<float>(framebufferWidth) /
            static_cast<float>(framebufferHeight);

        model.mat->shader->setMat4(
            "proj",
            current_cam->getProjectionMatrix(aspectRatio)
        );
    }

    //setting the view matrix unifrom
    model.mat->shader->setMat4(
        "view", current_cam->getViewMatrix()
    );

    //setting the actual transform matrix unifrom
    model.mat->shader->setMat4(
        "model",
        model.transform.getModelMatrix()
    );

    model.mat->shader->setVec3(
        "camPos",
        {
            current_cam->getPos()
        }
    );

    //apply light info to shader
    light.ApplyToShader(*(model.mat->shader));
    //apply mat info to shader
    model.mat->ApplyMaterial(*(model.mat->shader));   

    //texture & draw
    // if no texture just draw 
    if (!(model.mat->texture)) {
        model.mat->shader->setBool("isTextured", false);
        model.mat->shader->setBool("isSpecularMap", false);

        model.mesh->draw();

      



    }
    else {
        glActiveTexture(GL_TEXTURE0);
        model.mat->shader->setBool("isTextured", true);
        model.mat->texture->Bind();


        if (model.mat->specular_map_tex)
        {
            model.mat->shader->setBool("isSpecularMap", true);

            glActiveTexture(GL_TEXTURE1);
            model.mat->specular_map_tex->Bind();

            model.mat->shader->setTex("tex1", 1);
        }
        else
        {
            model.mat->shader->setBool("isSpecularMap", false);
        }




        model.mat->shader->setTex("tex0",  0);

        model.mesh->draw();
        
        glActiveTexture(GL_TEXTURE0);
        model.mat->texture->UnBind();


        if (model.mat->specular_map_tex) {
            glActiveTexture(GL_TEXTURE1);
            model.mat->specular_map_tex->UnBind();
        }


    }

}


