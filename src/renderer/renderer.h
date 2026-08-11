#pragma once
#include "./camera/camera.h"
#include "components/light/light.h"
#include "components/model/model.h"
#include <GLFW/glfw3.h>
#include <vector>

struct Scene {

	int id;
	char* name;

	std::vector<Model*> models;
	std::vector<Light*> lights;
	Camera* current_cam = nullptr;

};

class Renderer {

	public:	
		Renderer() {};

		Camera* current_cam = nullptr;
		GLFWwindow* window = nullptr;

		void renderModel(Model& model);
		void renderModel(Model& model, Light& light);
		void renderSceneModel(Model& model) const;
		void renderScene(Scene& scene) const;
};