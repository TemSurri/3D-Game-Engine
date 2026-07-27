#include "renderer.h"
#include <iostream>

void Renderer::renderModel(Model& model) {

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
    
    //texture & draw 

    model.mat->texture->Bind();

    model.mat->shader->setTex(*(model.mat->texture));

    model.mesh->draw();

    model.mat->texture->UnBind();
}