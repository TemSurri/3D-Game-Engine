#include "core/window_manager.h"
#include "renderer/shader/shader.h"
#include "renderer/components/model/model.h"
#include "renderer/camera/camera.h"
#include "renderer/renderer.h"
#include "renderer/components/light/light.h"

#include <stb_image.h>
#include <iostream>
#include <vector>


int main()
{
    //window
    WindowManager windowManager;

    GLFWwindow* window = windowManager.getWindow();

    if (!window)
    {
        return -1;
    }


    //pyramid mesh
    Mesh pyramidMesh;

    glm::vec3 frontNormal{ 0.0f, 0.707f, 0.707f };
    glm::vec3 rightNormal{ 0.707f, 0.707f, 0.0f };
    glm::vec3 backNormal{ 0.0f, 0.707f, -0.707f };
    glm::vec3 leftNormal{ -0.707f, 0.707f, 0.0f };
    glm::vec3 bottomNormal{ 0.0f, -1.0f, 0.0f };


    //front
    pyramidMesh.addVertex(Vertex{
        -0.4f, -0.4f,  0.4f,
         1.0f,  1.0f,  1.0f,
         0.0f,  0.0f,
         frontNormal
        });

    pyramidMesh.addVertex(Vertex{
         0.4f, -0.4f,  0.4f,
         1.0f,  1.0f,  1.0f,
         1.0f,  0.0f,
         frontNormal
        });

    pyramidMesh.addVertex(Vertex{
         0.0f,  0.5f,  0.0f,
         1.0f,  1.0f,  1.0f,
         0.5f,  1.0f,
         frontNormal
        });


    //right
    pyramidMesh.addVertex(Vertex{
         0.4f, -0.4f,  0.4f,
         1.0f,  1.0f,  1.0f,
         0.0f,  0.0f,
         rightNormal
        });

    pyramidMesh.addVertex(Vertex{
         0.4f, -0.4f, -0.4f,
         1.0f,  1.0f,  1.0f,
         1.0f,  0.0f,
         rightNormal
        });

    pyramidMesh.addVertex(Vertex{
         0.0f,  0.5f,  0.0f,
         1.0f,  1.0f,  1.0f,
         0.5f,  1.0f,
         rightNormal
        });


    //back
    pyramidMesh.addVertex(Vertex{
         0.4f, -0.4f, -0.4f,
         1.0f,  1.0f,  1.0f,
         0.0f,  0.0f,
         backNormal
        });

    pyramidMesh.addVertex(Vertex{
        -0.4f, -0.4f, -0.4f,
         1.0f,  1.0f,  1.0f,
         1.0f,  0.0f,
         backNormal
        });

    pyramidMesh.addVertex(Vertex{
         0.0f,  0.5f,  0.0f,
         1.0f,  1.0f,  1.0f,
         0.5f,  1.0f,
         backNormal
        });


    //left
    pyramidMesh.addVertex(Vertex{
        -0.4f, -0.4f, -0.4f,
         1.0f,  1.0f,  1.0f,
         0.0f,  0.0f,
         leftNormal
        });

    pyramidMesh.addVertex(Vertex{
        -0.4f, -0.4f,  0.4f,
         1.0f,  1.0f,  1.0f,
         1.0f,  0.0f,
         leftNormal
        });

    pyramidMesh.addVertex(Vertex{
         0.0f,  0.5f,  0.0f,
         1.0f,  1.0f,  1.0f,
         0.5f,  1.0f,
         leftNormal
        });


    //bottom
    pyramidMesh.addVertex(Vertex{
        -0.4f, -0.4f,  0.4f,
         1.0f,  1.0f,  1.0f,
         0.0f,  0.0f,
         bottomNormal
        });

    pyramidMesh.addVertex(Vertex{
         0.4f, -0.4f,  0.4f,
         1.0f,  1.0f,  1.0f,
         1.0f,  0.0f,
         bottomNormal
        });

    pyramidMesh.addVertex(Vertex{
         0.4f, -0.4f, -0.4f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,
         bottomNormal
        });

    pyramidMesh.addVertex(Vertex{
        -0.4f, -0.4f, -0.4f,
         1.0f,  1.0f,  1.0f,
         0.0f,  1.0f,
         bottomNormal
        });


    //pyramid inds
    pyramidMesh.addTriangle(0, 1, 2);
    pyramidMesh.addTriangle(3, 4, 5);
    pyramidMesh.addTriangle(6, 7, 8);
    pyramidMesh.addTriangle(9, 10, 11);

    pyramidMesh.addTriangle(12, 14, 13);
    pyramidMesh.addTriangle(12, 15, 14);

    pyramidMesh.initGLResources();


    //sphere mesh
    Mesh sphereMesh;

    const int stacks = 24;
    const int slices = 32;
    const float sphereRadius = 0.5f;

    for (int stack = 0; stack <= stacks; stack++)
    {
        float v =
            static_cast<float>(stack) /
            static_cast<float>(stacks);

        float phi =
            v * glm::pi<float>();

        for (int slice = 0; slice <= slices; slice++)
        {
            float u =
                static_cast<float>(slice) /
                static_cast<float>(slices);

            float theta =
                u * glm::two_pi<float>();

            float x =
                sphereRadius * sin(phi) * cos(theta);

            float y =
                sphereRadius * cos(phi);

            float z =
                sphereRadius * sin(phi) * sin(theta);

            glm::vec3 normal{
                x / sphereRadius,
                y / sphereRadius,
                z / sphereRadius
            };

            sphereMesh.addVertex(Vertex{
                x, y, z,

                //color
                1.0f, 1.0f, 1.0f,

                //uv
                u, v,

                normal
                });
        }
    }


    //sphere inds
    for (int stack = 0; stack < stacks; stack++)
    {
        for (int slice = 0; slice < slices; slice++)
        {
            int current =
                stack * (slices + 1) + slice;

            int next =
                current + slices + 1;

            sphereMesh.addTriangle(
                current,
                next,
                current + 1
            );

            sphereMesh.addTriangle(
                current + 1,
                next,
                next + 1
            );
        }
    }

    sphereMesh.initGLResources();


    //floor mesh
    Mesh floorMesh;

    floorMesh.addVertex(Vertex{
        -0.5f, 0.0f, -0.5f,
         1.0f, 1.0f, 1.0f,
         0.0f, 0.0f,
         {0.0f, 1.0f, 0.0f}
        });

    floorMesh.addVertex(Vertex{
         0.5f, 0.0f, -0.5f,
         1.0f, 1.0f, 1.0f,
         1.0f, 0.0f,
         {0.0f, 1.0f, 0.0f}
        });

    floorMesh.addVertex(Vertex{
         0.5f, 0.0f, 0.5f,
         1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,
         {0.0f, 1.0f, 0.0f}
        });

    floorMesh.addVertex(Vertex{
        -0.5f, 0.0f, 0.5f,
         1.0f, 1.0f, 1.0f,
         0.0f, 1.0f,
         {0.0f, 1.0f, 0.0f}
        });

    floorMesh.addTriangle(0, 1, 2);
    floorMesh.addTriangle(0, 2, 3);

    floorMesh.initGLResources();


    //camera
    Camera cam;


    //shaders
    Shader lightingShader(
        "renderer/shader/mat_shaders/mat_multi_light.vert",
        "renderer/shader/mat_shaders/mat_multi_light.frag"
    );

    //textures
    Tex floorTexture;
    floorTexture.Create(
        "resources/textures/tile4k.jpg"
    );

    Tex floorSpec;
    floorSpec.Create(
        "resources/textures/tile_specmap4k.jpg"
    );

    Tex pyramidTexture;
    pyramidTexture.Create(
        "resources/textures/bri.jpg"
    );

    Tex pyramidSpec;
    pyramidSpec.Create(
        "resources/textures/bri_specmap.jpg"
    );

    Tex sphereTexture;
    sphereTexture.Create(
        "resources/textures/flesh.jpg"
    );


    //floor mat
    Material floorMat;

    floorMat.shader = &lightingShader;
    floorMat.texture = &floorTexture;
    floorMat.specular_map_tex = &floorSpec;

    floorMat.diffuse = 1.5f;
    floorMat.specStrength = 2.5f;
    floorMat.specPower = 24.0f;
    floorMat.ambience = 1.04f;
    floorMat.tiling = { 1.0f, 1.0f };


    //pyramid mat
    Material pyramidMat;

    pyramidMat.shader = &lightingShader;
    pyramidMat.texture = &pyramidTexture;
    pyramidMat.specular_map_tex = &pyramidSpec;

    pyramidMat.diffuse = 1.0f;
    pyramidMat.specStrength = 3.0f;
    pyramidMat.specPower = 20.0f;
    pyramidMat.ambience = 0.08f;


    //sphere mat
    Material sphereMat;

    sphereMat.shader = &lightingShader;

    sphereMat.diffuse = 1.2f;
    sphereMat.specStrength = 5.0f;
    sphereMat.specPower = 32.0f;
    sphereMat.ambience = 1.06f;

    

    //models
    Model floor{"tiled floor", 1};
    floor.mesh = &floorMesh;
    floor.mat = &floorMat;

    //lights
    Light l1{1.0f,1.0f,1.0f,1.0f, POINT};
    l1.transform.position = { 1.0, 1.0, 1.0 };
    
    Model lo{ "light obj", 2 };
    lo.mat = &sphereMat;
    lo.mesh = &sphereMesh;
   
    lo.transform = l1.transform;

    //scene
    Scene scene;
    scene.current_cam = &cam;
    scene.models.push_back(&lo);
    scene.models.push_back(&floor);
    scene.lights.push_back(&l1);

    //renderer
    Renderer renderer;

    renderer.window = window;

    glEnable(GL_DEPTH_TEST);


    //time stuff
    double fpsLastTime = glfwGetTime();
    double lastFrameTime = glfwGetTime();

    int frameCount = 0;
    double fps = 0.0;


    //main loop
    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();

        float deltaTime =
            static_cast<float>(
                currentTime - lastFrameTime
                );

        lastFrameTime = currentTime;

        float t =
            static_cast<float>(currentTime);


        //fps
        frameCount++;

        if (currentTime - fpsLastTime >= 1.0)
        {
            fps =
                frameCount /
                (currentTime - fpsLastTime);

            frameCount = 0;
            fpsLastTime = currentTime;

            std::cout
                << "FPS: "
                << fps
                << '\n';

            glfwSetWindowTitle(
                window,
                (
                    "My Engine | FPS: " +
                    std::to_string(
                        static_cast<int>(fps)
                    )
                    ).c_str()
            );
        }


        //clear
        glClearColor(
            0.02f,
            0.02f,
            0.035f,
            1.0f
        );

        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );


        //camera input
        cam.inputs(window);


        //draw scene
        renderer.renderScene(scene);


        //end frame
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    //cleanup
    windowManager.disposeWindow(window);

    return 0;
}