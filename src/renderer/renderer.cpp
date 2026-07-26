#include "renderer.h"

void Renderer::renderModel(Model& model) {

	//check if model even has mat and or mesh
	if (!(model.mat)) {
		return;
	}
    if (!(model.mesh)) {
        return;
    }
	// no shader
	if (!(model.mat->shader)) {
		return;

	}

    // no camera
    if (!(current_cam)) {
        return;
    }

    model.mesh->vao.Bind();

    int framebufferWidth = 0;
    int framebufferHeight = 0;

    glfwGetFramebufferSize(
        window,
        &framebufferWidth,
        &framebufferHeight
    );

    //setting up unforms
    model.mesh->vao.Bind();
    model.mat->shader->Activate();


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

    model.mat->shader->setMat4(
        "view", current_cam->getViewMatrix()
    );

    model.mat->shader->setMat4(
        "model",
        model.transform.getModelMatrix()
    );

    model.mesh->draw();

}