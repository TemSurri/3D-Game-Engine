#pragma once
#include <glad/glad.h>
#include "vbo.h"


class VAO {



public:
	GLuint ID{};

	VAO();
	~VAO();

	//delete all copy constructors
	VAO(const VAO& other) = delete;
	VAO& operator=(const VAO& other) = delete;

	//create move contrsuctors
	VAO(VAO& other) noexcept
		:ID(other.ID)
	{
		other.ID = 0;
	};

	// move operator
	VAO& operator=(VAO&& other) noexcept {
		if (this != &other) {

			if (ID != 0) {
				glDeleteBuffers(1, &ID);
			}

			ID = other.ID;
			other.ID = 0;

		}


		return *this;
	};

	void LinkAttrib(const VBO& vbo, GLuint layout, GLuint numComponenets, GLenum type, GLsizei stride, const void* offset);
	void Bind();
	void Unbind();
	void Delete();





};