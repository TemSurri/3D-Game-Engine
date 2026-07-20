#pragma once
#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    enum ERROR
    {
        UNKNOWN,
        FILE_READ_FAILED
    };

    struct ErrorObj
    {
        ERROR error = UNKNOWN;
        const char* error_msg;
    };

    GLuint ID = 0;

    Shader() = default;

    Shader(
        const char* vertexFile,
        const char* fragmentFile
    );

    ~Shader()
    {
        if (ID != 0)
        {
            glDeleteProgram(ID);
        }
    }

    // No copying
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    // Move constructor
    Shader(Shader&& other) noexcept
        : ID(other.ID)
    {
        // The old object no longer owns the program.
        other.ID = 0;
    }

    // Move assignment
    Shader& operator=(Shader&& other) noexcept
    {
        if (this != &other)
        {
            // Delete anything currently owned by this object.
            if (ID != 0)
            {
                glDeleteProgram(ID);
            }

            // Take ownership from other.
            ID = other.ID;

            // Prevent other's destructor from deleting it.
            other.ID = 0;
        }

        return *this;
    }

    void Activate() const
    {
        glUseProgram(ID);
    }

    void Delete()
    {
        if (ID != 0)
        {
            glDeleteProgram(ID);
            ID = 0;
        }
    }

    // set the uniform within the shader
    void setMat4(const std::string& name, const glm::mat4& matrix);

private:
    static std::string readFile(const char* filepath);
};