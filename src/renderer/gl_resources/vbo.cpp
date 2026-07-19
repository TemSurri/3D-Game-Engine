#include "vbo.h";




VBO::VBO(const void* data, GLsizeiptr size ) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
};

VBO::~VBO() {

    if (ID != 0)
    {
        glDeleteBuffers(1, &ID);
        ID = 0;
    }

}

void VBO::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
};

void VBO::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
};

void VBO::Delete() {
    if (ID != 0)
    {
        glDeleteBuffers(1, &ID);
        ID = 0;
    }
};