#pragma once
#include <stb_image.h>
#include <glad/glad.h>

class Tex {

	public:

		GLuint ID{};

		Tex() {};
		~Tex() {
			glDeleteTextures(1, &ID);
		}

		//no copying
		Tex(const Tex& other) = delete;
		Tex& operator=(const Tex& other) = delete;

		//move operator
		Tex(Tex&& other) noexcept :ID(other.ID){
			other.ID = 0;
		}

		Tex& operator=(Tex&& other) noexcept {
			if (this != &other) {

				if (ID != 0) {
					glDeleteTextures(1, &ID);
				}

				ID = other.ID;
				other.ID = 0;

			}
			return *this;
		};


		void Create(const char* texFile);
		void Bind() const;
		void UnBind() const;
};
