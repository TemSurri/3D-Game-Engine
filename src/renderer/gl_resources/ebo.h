#pragma once
#include <glad/glad.h>

class EBO {

public:
	GLuint ID{};

	EBO() {};
	~EBO();

	//delete all copy constructors
	EBO(const EBO& other) = delete;
	EBO& operator=(const EBO& other) = delete;

	//create move contrsuctors
	EBO(EBO& other) noexcept
		:ID(other.ID)
	{
		other.ID = 0;
	};

	// move operator
	EBO& operator=(EBO&& other) noexcept {
		if (this != &other) {

			if (ID != 0) {
				glDeleteBuffers(1, &ID);
			}

			ID = other.ID;
			other.ID = 0;

		}


		return *this;
	};

	void Upload(const GLuint* indices, GLsizeiptr size);
	void Bind();
	void Unbind();
	void Delete();





};