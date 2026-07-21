#include "core/window_manager.h"
#include "renderer/model/mesh.h"
#include "renderer/shader/shader.h"
#include "renderer/model/transform.h"
#include "renderer/model/model.h"

int main()
{
    WindowManager windowManager;

    GLFWwindow* window = windowManager.getWindow();

    if (window == nullptr)
    {
        return -1;
    }

    //MESH CREATION
    // Front face vertices
    Vertex v0{
        -0.3f, -0.3f,  0.3f,
         1.0f,  0.0f,  0.0f
    };

    Vertex v1{
         0.3f, -0.3f,  0.3f,
         0.0f,  1.0f,  0.0f
    };

    Vertex v2{
         0.3f,  0.3f,  0.3f,
         0.0f,  0.0f,  1.0f
    };

    Vertex v3{
        -0.3f,  0.3f,  0.3f,
         1.0f,  1.0f,  0.0f
    };

    // Back face vertices
    Vertex v4{
        -0.3f, -0.3f, -0.3f,
         1.0f,  0.0f,  1.0f
    };

    Vertex v5{
         0.3f, -0.3f, -0.3f,
         0.0f,  1.0f,  1.0f
    };

    Vertex v6{
         0.3f,  0.3f, -0.3f,
         1.0f,  1.0f,  1.0f
    };

    Vertex v7{
        -0.3f,  0.3f, -0.3f,
         0.4f,  0.4f,  0.4f
    };

    Mesh m;

    m.addVertex(v0);
    m.addVertex(v1);
    m.addVertex(v2);
    m.addVertex(v3);
    m.addVertex(v4);
    m.addVertex(v5);
    m.addVertex(v6);
    m.addVertex(v7);


    // Front face
    m.addTriangle(0, 1, 2);
    m.addTriangle(2, 3, 0);

    // Back face
    m.addTriangle(5, 4, 7);
    m.addTriangle(7, 6, 5);

    // Left face
    m.addTriangle(4, 0, 3);
    m.addTriangle(3, 7, 4);

    // Right face
    m.addTriangle(1, 5, 6);
    m.addTriangle(6, 2, 1);

    // Top face
    m.addTriangle(3, 2, 6);
    m.addTriangle(6, 7, 3);

    // Bottom face
    m.addTriangle(4, 5, 1);
    m.addTriangle(1, 0, 4);
    m.initGLResources();

    //SHADER CREATION
    Shader shaderColor = Shader("renderer/shader/color.vert", "renderer/shader/color.frag");
    shaderColor.Activate();
    m.vao.Bind();

    //TRANSFROM CREATION
    Transform transform;


    //PROJ and VIEW

    glm::mat4 proj = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(45.0f), float(800.0f / 800.0f), 0.1f, 100.0f);
    view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));

    const GLint projlocation = glGetUniformLocation(
        shaderColor.ID,
        "proj"
    );

    glUniformMatrix4fv(
        projlocation,
        1,
        GL_FALSE,
        glm::value_ptr(proj)
    );

    const GLint viewlocation = glGetUniformLocation(
        shaderColor.ID,
        "view"
    );

    glUniformMatrix4fv(
        viewlocation,
        1,
        GL_FALSE,
        glm::value_ptr(view)
    );




    //model testing

    Model cube1 = Model();
    cube1.mesh = &m;

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

        
        const float movementSpeed = 0.001f;
        const float rotateSpeed = 0.004f;

        cube1.render(shaderColor);

        //rotation
        if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        {
            cube1.transform.rotation.x += rotateSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        {
            cube1.transform.rotation.y += rotateSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        {
            cube1.transform.rotation.z += rotateSpeed;
        }

        //translation
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            cube1.transform.position.y += movementSpeed;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            cube1.transform.position.y -= movementSpeed;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            cube1.transform.position.x -= movementSpeed;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            cube1.transform.position.x += movementSpeed;
        }

        if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
        {
            cube1.transform.position.z -= movementSpeed;
        }

        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        {
            cube1.transform.position.z += movementSpeed;
        }


        
       
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }





    shaderColor.Delete();
    windowManager.disposeWindow(window);

    return 0;
}