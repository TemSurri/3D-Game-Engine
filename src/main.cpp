#include "core/window_manager.h"
#include "renderer/mesh.h"
#include "renderer/shader/shader.h"
#include "renderer/transform.h"

int main()
{
    WindowManager windowManager;

    GLFWwindow* window = windowManager.getWindow();

    if (window == nullptr)
    {
        return -1;
    }

    Vertex v0{
        0.1f, 0.4, 0.0f, 0.0f, 0.3f, 0.3f
    };

    Vertex v1{
        0.6f, 0.3, 0.0f, 0.5f, 0.1f, 0.3f
    };

    Vertex v2{
        0.9f, 0.6, 0.0f, 0.9f, 0.1f, 0.3f
    };

    Vertex v3{
        0.1f, 0.2, 0.0f, 0.9f, 0.1f, 0.3f
    };


    Mesh m = Mesh();
    m.addVertex(v0);
    m.addVertex(v1);
    m.addVertex(v2);
    m.addVertex(v3);

    m.addTriangle(0, 1, 2);
    m.addTriangle(3, 0, 1);
    m.initGLResources();

    Shader shaderColor = Shader("renderer/shader/color.vert", "renderer/shader/color.frag");
    shaderColor.Activate();
    m.vao.Bind();


    Transform transform;


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderColor.setMat4(
            "model",
            transform.getModelMatrix()
        );
        const float movementSpeed = 0.001f;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            transform.position.y += movementSpeed;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            transform.position.y -= movementSpeed;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            transform.position.x -= movementSpeed;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            transform.position.x += movementSpeed;
        }

        
        glDrawElements(
            GL_TRIANGLES,
            6,
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