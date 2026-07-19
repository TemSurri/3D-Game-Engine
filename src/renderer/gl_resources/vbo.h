#pragma once
#include <glad/glad.h>

class VBO {



public:
	GLuint ID{};

	VBO(const void* data, GLsizeiptr size);
	~VBO();

	//delete all copy constructors
	VBO(const VBO& other) = delete;
	VBO& operator=(const VBO& other) = delete;

	//create move contrsuctors
	VBO(VBO& other) noexcept
		:ID(other.ID)
	{
		other.ID = 0;
	};

	// move operator
	VBO& operator=(VBO&& other) noexcept {
		if (this != &other) {

			if (ID != 0) {
				glDeleteBuffers(1, &ID);
			}

			ID = other.ID;
			other.ID = 0;

		}


		return *this;
	};


	void Bind() const;
	void Unbind();
	void Delete();

};