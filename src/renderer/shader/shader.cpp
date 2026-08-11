#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

#include "../components/light/light.h"

std::string Shader::readFile(const char* filepath)
{
    std::ifstream file(filepath);

    if (!file.is_open())
    {
        throw ErrorObj{
            FILE_READ_FAILED,
            "Failed to open"
        };
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {

    std::string vertexCode = readFile(vertexFile);
    std::string fragmentCode = readFile(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    glLinkProgram(ID);

    GLint success = 0;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if (!success)
    {
        char infoLog[1024]{};

        glGetProgramInfoLog(
            ID,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cerr << "Shader program linking failed:\n"
            << infoLog << '\n';
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    
}

void Shader::setMat4(const std::string& name, const glm::mat4& matrix
) const {
    const GLint location = glGetUniformLocation(
        ID,
        name.c_str()
    );

    glUniformMatrix4fv(
        location,
        1,
        GL_FALSE,
        glm::value_ptr(matrix)
    );
}

void Shader::setVec3(const std::string& name, const glm::vec3& vec
) const {
    const GLint location = glGetUniformLocation(
        ID,
        name.c_str()
    );

    glUniform3fv(
        location,
        1,
        glm::value_ptr(vec)
    );
}

void Shader::setVec2(const std::string& name, const glm::vec2& vec) const {
    const GLint location = glGetUniformLocation(
        ID,
        name.c_str()
    );

    glUniform2fv(
        location,
        1,
        glm::value_ptr(vec)
    );

}

void Shader::setTex(const std::string& name, int textureUnit) const {

    GLint location = glGetUniformLocation(
        ID,
        name.c_str()
    );

    glUniform1i(location, textureUnit);
    
    
};

void Shader::setBool(const std::string& name, bool val) const {

    GLint location = glGetUniformLocation(
        ID,
        name.c_str()
    );

    glUniform1i(location, val);


}

void Shader::setFloat(const std::string& name, float val) const {

    GLint location = glGetUniformLocation(
        ID,
        name.c_str()
    );

    glUniform1f(location, val);


}

void Shader::setInt(const std::string& name, int val) const {

    GLint location = glGetUniformLocation(
        ID,
        name.c_str()
    );

    glUniform1i(location, val);


}


void Shader::applySceneLights(const std::vector<Light*>& lights) const {
    constexpr int MAX_LIGHTS = 16;

    int count = std::min(
        static_cast<int>(lights.size()),
        MAX_LIGHTS
    );

    setInt("light_count", count);

    for (int i = 0; i < count; i++)
    {
        auto light = lights[i];

        std::string base = "lights[" + std::to_string(i) + "]";

        setInt(
            base + ".type",
            static_cast<int>(light->getType())
        );

        setVec3(
            base + ".pos",
            light->transform.position
        );

        setVec3(
            base + ".dir",
            light->transform.rotation // if this is actually your direction
        );

        auto light_props = light->getProps();


        setFloat(
            base + ".intensity",
            light_props.intensity
        );

        setFloat(
            base + ".radius",
            light_props.radius
        );

        setVec3(
            base + ".color",
            light_props.color
        );

        setFloat(
            base + ".innerCutoff",
            light_props.innerCutoff
        );

        setFloat(
            base + ".outerCutoff",
            light_props.outerCutoff
        );

        
    }



};


void Shader::applySceneCamera(const Camera& camera, GLFWwindow* window) const {
    int framebufferWidth = 0;
    int framebufferHeight = 0;

    glfwGetFramebufferSize(
        window,
        &framebufferWidth,
        &framebufferHeight
    );

    //setting the projection matrix unifrom
    if (framebufferWidth > 0 && framebufferHeight > 0)
    {
        glViewport(
            0,
            0,
            framebufferWidth,
            framebufferHeight
        );

        const float aspectRatio =
            static_cast<float>(framebufferWidth) /
            static_cast<float>(framebufferHeight);

        setMat4(
            "proj",
            camera.getProjectionMatrix(aspectRatio)
        );
    }

    //setting the view matrix unifrom
    setMat4(
        "view", camera.getViewMatrix()
    );

    setVec3(
        "camPos",
        {
            camera.getPos()
        }
    );

};