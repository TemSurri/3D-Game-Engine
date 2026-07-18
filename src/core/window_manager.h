#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class WindowManager {

public:
	
	GLFWwindow* getWindow();

	void disposeWindow(GLFWwindow* window);

	static void framebufferSizeCallback(
		GLFWwindow* window,
		int width,
		int height);

};