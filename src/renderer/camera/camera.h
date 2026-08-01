#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
	private: 

		//default camera configs
		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		//camera movement
		float yaw{ -90.0f };
		float pitch{ 0.0f };

		float movementSpeed = 0.0005f;
		float rotateSpeed = 0.004f;
		float lookSpeed = 70.0f * 0.0002;
		float mouseSensitivity = 0.1f;

		double previousMouseX = 0.0;
		double previousMouseY = 0.0;

		bool firstMouseInput = true;

		// projection
		float fov = 45.0f;
		float nearPlane = 0.1f;
		float farPlane = 100.0f;

	public:
		Camera() {

		};

		

		

		glm::mat4 getViewMatrix() const;
		glm::mat4 getProjectionMatrix(float aspectRatio) const;
		glm::vec3 getPos() const;

		
		void updateDirection();
		void inputs(GLFWwindow* window);








};