#pragma once
#include "./camera/camera.h"
#include "./components/model/model.h"
#include "./components/light/light.h"
#include <GLFW/glfw3.h>

class Renderer {

	public:	
		Renderer() {};

		Camera* current_cam = nullptr;
		GLFWwindow* window = nullptr;

		void renderModel(Model& model);
		void renderModel(Model& model, Light& light);
};