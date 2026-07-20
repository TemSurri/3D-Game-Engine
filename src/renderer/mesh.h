#include <iostream>
#include <vector>
#include <cstddef>
#include "gl_resources/ebo.h"
#include "gl_resources/vbo.h"
#include "gl_resources/vao.h"


struct Vertex {
	float x{};
	float y{};
	float z{};

	float r{};
	float g{};
	float b{};

	float u{};
	float v{};

};

class Mesh {

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

public:
	Mesh() {};

	//owns its own gl resources
	VBO vbo = VBO();
	EBO ebo = EBO();
	VAO vao = VAO();

	void addTriangle(
		unsigned int a,
		unsigned int b,
		unsigned int c
	);
	void addVertex(const Vertex& v);
	void initGLResources();
};