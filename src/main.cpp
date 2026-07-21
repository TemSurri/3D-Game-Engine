#include "core/window_manager.h"
#include "renderer/shader/shader.h"
#include "renderer/model/model.h"
#include "renderer/camera/camera.h"

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
    Camera cam = Camera();
    //model testing

    Model cube1 = Model();
    cube1.mesh = &m;

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

        
        const float movementSpeed = 0.0005f;
        const float rotateSpeed = 0.004f;

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

        // Camera movement
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            cam.pos += cam.front * movementSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            cam.pos -= cam.front * movementSpeed;
        }
        glm::vec3 right = glm::normalize(glm::cross(cam.front, cam.up));
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            cam.pos -= right * movementSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            cam.pos += right * movementSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            cam.pos += cam.up * movementSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            cam.pos -= cam.up * movementSpeed;
        }
        const float lookSpeed = 70.0f * 0.0002;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            cam.yaw -= lookSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            cam.yaw += lookSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            cam.pitch += lookSpeed;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            cam.pitch -= lookSpeed;
        }
        cam.pitch = glm::clamp(cam.pitch, -89.0f, 89.0f);
        cam.updateDirection();
        
        
        int framebufferWidth = 0;
        int framebufferHeight = 0;

        glfwGetFramebufferSize(
            window,
            &framebufferWidth,
            &framebufferHeight
        );

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

            shaderColor.setMat4(
                "proj",
                cam.getProjectionMatrix(aspectRatio)
            );
        }

        shaderColor.setMat4(
            "view", cam.getViewMatrix()
        );
        cube1.render(shaderColor);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }





    shaderColor.Delete();
    windowManager.disposeWindow(window);

    return 0;
}