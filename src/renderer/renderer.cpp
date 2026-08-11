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




        model.mat->shader->setTex("tex0", 0);

        model.mesh->draw();

        glActiveTexture(GL_TEXTURE0);
        model.mat->texture->UnBind();


        if (model.mat->specular_map_tex) {
            glActiveTexture(GL_TEXTURE1);
            model.mat->specular_map_tex->UnBind();
        }


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



// RENDERING SCENES : Making use of the mat_multi_light.frag shader
void Renderer::renderSceneModel(Model& model) const
{
    Shader& shader = *model.mat->shader;

    shader.setMat4(
        "model",
        model.transform.getModelMatrix()
    );

    model.mesh->draw();
}

// takes care of error handling in entire pipeline and renders each model in a scene
void Renderer::renderScene(Scene& scene) const {




    // scene error check
    if (!scene.current_cam) {
        std::cout << "scene has no cam" << std::endl;
        return;
    }

    Shader* current_bound_shader = nullptr;
    Material* boundMaterial = nullptr;


    //max of 5 active shaders;
    const int MAX_SHADER = 5;
    int scene_detail_already_added_shaders[MAX_SHADER]{0};

    for (Model* modelptr : scene.models) {

        Model& model = *modelptr;

        if (!model.mat) {
            std::cout << "a Model has no mat" << std::endl;
            continue;
        }
       
        Shader* current_shader = model.mat->shader;
        //error handle
        if (!current_shader){
            std::cout << "a models mat has no shader" << std::endl;
            continue;
        }

        if (!(model.mesh)) {
            std::cout << "model has no mesh" << std::endl;
            continue;
        }

        if (current_bound_shader != current_shader) {
            
            current_shader->Activate();
            current_bound_shader = current_shader;
            
        }      

        bool scene_detail_added = false;
        int safe_insert = -1;

        //sees if current shader is already active, if not it gets an available index to safely add it to
        for (int i{}; i < MAX_SHADER; i++) {

            if (scene_detail_already_added_shaders[i] == current_shader->ID) {
                scene_detail_added = true;
            }
            else if (scene_detail_already_added_shaders[i] == 0) {
                safe_insert = i;
            }
        }

        if (!scene_detail_added) {
            if (safe_insert < 0) {
                std::cout << "Too many shaders" << std::endl;
                return;
            }
            scene_detail_already_added_shaders[safe_insert] = current_shader->ID;

            // will apply all scene specific details to shader
            current_shader->applySceneLights(scene.lights);
            current_shader->applySceneCamera(*(scene.current_cam), window);
        }

        if (boundMaterial != model.mat) {

            model.mat->Bind(*current_shader);
            boundMaterial = model.mat;

        }

        renderSceneModel(model);

    }
};
