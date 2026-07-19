#include "core/window_manager.h"
#include "renderer/shader/shader.h"
#include "renderer/gl_resources/vao.h"
#include "renderer/gl_resources/ebo.h"

int main()
{
    WindowManager windowManager;

    GLFWwindow* window = windowManager.getWindow();

    if (window == nullptr)
    {
        return -1;
    }


    GLfloat vertices[]{
        0.1f, 0.5f, 0.0f, 0.0f, 0.3f, 0.3f,
        0.1f, 0.3f, .0f, 0.9f, 0.3f, 0.3f,
        0.9f, 0.3f, .0f, 0.0f, 0.7f, 0.3f,
    };

    GLuint indices[]{
        0,1,2,
        2,1,0,
        1,0,2

    };

    VAO vao= VAO();
    VBO vbo = VBO(vertices, sizeof(vertices));
    
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(GLfloat) * 6, (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(GLfloat) * 6, reinterpret_cast<void*>(sizeof(GLfloat)*3));

    EBO ebo = EBO(indices, sizeof(indices));
    



    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    Shader shaderColor = Shader("renderer/shader/color.vert", "renderer/shader/color.frag");
    shaderColor.Activate();
    vao.Bind();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        

        
        glDrawElements(
            GL_TRIANGLES,
            3,
            GL_UNSIGNED_INT,
            nullptr
        );
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }





    shaderColor.Delete();
    windowManager.disposeWindow(window);

    return 0;
}