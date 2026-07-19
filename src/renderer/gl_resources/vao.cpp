#include "vao.h";




VAO::VAO() {
    glGenVertexArrays(1, &ID);
};

VAO::~VAO() {

    if (ID != 0)
    {
        glDeleteVertexArrays(1, &ID);
    }

}

void::VAO::LinkAttrib(const VBO& vbo, GLuint layout, GLuint numComponenets, GLenum type, GLsizei stride, const void* offset) {
    Bind();
    vbo.Bind();

    glVertexAttribPointer(layout, numComponenets, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);

};

void VAO::Bind() {
    glBindVertexArray(ID);
};

void VAO::Unbind() {
    glBindVertexArray(0);
};

void VAO::Delete() {
    if (ID != 0)
    {
        glDeleteVertexArrays(1, &ID);
        ID = 0;
    }
};