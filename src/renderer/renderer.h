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

		GLFWwindow* window = nullptr;

		// renders model from scene
		void renderSceneModel(Model& model) const;

		// renders scene
		void renderScene(Scene& scene) const;
};