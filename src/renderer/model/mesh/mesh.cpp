#include "mesh.h"

void Mesh::addVertex(const Vertex& v) {

	vertices.push_back(v);

}

void Mesh::addTriangle(
    unsigned int a,
    unsigned int b,
    unsigned int c
)
{
    indices.push_back(a);
    indices.push_back(b);
    indices.push_back(c);
}

// updates the current gl_resources to hold and interpret the current indices and vertices
void Mesh::initGLResources() {

    // error checks, situations that make it so either gl_ressource initialization will error or just be weird
    if (vertices.empty())
    {
        throw std::runtime_error("Cannot initialize a mesh with no vertices");
    }

    if (indices.empty())
    {
        throw std::runtime_error("Cannot initialize a mesh with no indices");
    }

    for (unsigned int index : indices)
    {
        if (index >= vertices.size())
        {
            throw std::runtime_error("Mesh index is out of range");
        }
    }


    vao.Create();

    vbo.Upload(vertices.data(), vertices.size() * sizeof(Vertex));

    // for xyz
    vao.LinkAttrib(
        vbo,
        0,
        3,
        GL_FLOAT,
        sizeof(Vertex),
        reinterpret_cast<void*>(offsetof(Vertex, x))
    );
    
    //for rgb
    vao.LinkAttrib(
        vbo,
        1,
        3,
        GL_FLOAT,
        sizeof(Vertex),
        reinterpret_cast<void*>(offsetof(Vertex, r))
    );

    //for uv
    vao.LinkAttrib(
        vbo,
        2,
        2,
        GL_FLOAT,
        sizeof(Vertex),
        reinterpret_cast<void*>(offsetof(Vertex, u))
    );

    ebo.Upload(indices.data(), indices.size() * sizeof(unsigned int));

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

void Mesh::draw() {

    //TODO
    //error check to see if initialized and drawable


    vao.Bind();

    glDrawElements(
        GL_TRIANGLES,
        indices.size(),
        GL_UNSIGNED_INT,
        nullptr
    );

    vao.Unbind();



};