#include "core/window_manager.h"
#include "renderer/shader/shader.h"
#include "renderer/model/model.h"
#include "renderer/camera/camera.h"
#include "renderer/renderer.h"
#include <stb_image.h>

int main()
{
    WindowManager windowManager;

    GLFWwindow* window = windowManager.getWindow();

    if (window == nullptr)
    {
        return -1;
    }

    Mesh m;

    const int stacks = 24;
    const int slices = 32;
    const float radius = 0.5f;

    for (int stack = 0; stack <= stacks; stack++)
    {
        float v = static_cast<float>(stack) / stacks;

        // 0 -> PI
        float phi = v * glm::pi<float>();

        for (int slice = 0; slice <= slices; slice++)
        {
            float u = static_cast<float>(slice) / slices;

            // 0 -> 2PI
            float theta = u * glm::two_pi<float>();

            float x = radius * sin(phi) * cos(theta);
            float y = radius * cos(phi);
            float z = radius * sin(phi) * sin(theta);

            Vertex vertex{
                x, y, z,

                // color
                1.0f, 1.0f, 1.0f,

                // UV
                u, v
            };

            m.addVertex(vertex);
        }
    }


    // Generate triangles
    for (int stack = 0; stack < stacks; stack++)
    {
        for (int slice = 0; slice < slices; slice++)
        {
            int current =
                stack * (slices + 1) + slice;

            int next =
                current + slices + 1;


            // Triangle 1
            m.addTriangle(
                current,
                next,
                current + 1
            );

            // Triangle 2
            m.addTriangle(
                current + 1,
                next,
                next + 1
            );
        }
    }

    m.initGLResources();

    //TRANSFROM CREATION
    //shit that provides the actual dimensions
    Transform transform;

    //CAM CREATION
    //create Cam, preconfigured view and proj matrix
    Camera cam = Camera();

    //create Mat
    //owns tex and shader for a model
    Material mat;
    Shader texShader = Shader("renderer/shader/tex.vert", "renderer/shader/tex.frag");
    mat.shader = &texShader;
    Tex fleshTex = Tex();
    fleshTex.Create("resources/textures/flesh.jpg");
    mat.texture = &fleshTex;

    //make renderer
    Renderer renderer = Renderer();

    renderer.current_cam = &cam;
    renderer.window = &(*window);


    //putting everything together in Model
    Model cube1 = Model();
    cube1.mesh = &m;
    cube1.mat = &mat;


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
        
        renderer.renderModel(cube1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    windowManager.disposeWindow(window);

    return 0;
}