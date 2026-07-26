#pragma once
#include "./camera/camera.h"
#include "./model/model.h"
#include <GLFW/glfw3.h>

class Renderer {

	public:	
		Renderer() {};

		Camera* current_cam = nullptr;
		GLFWwindow* window = nullptr;

		void renderModel(Model& model);
		
};