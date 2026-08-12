#include "renderer.h"
#include <iostream>

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


            current_shader->applyModelMat(model);
            boundMaterial = model.mat;

        }

        renderSceneModel(model);

    }
};
