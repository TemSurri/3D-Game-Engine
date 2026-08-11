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
        "renderer/shader/mat_shaders/mat_single_light.vert",
        "renderer/shader/mat_shaders/mat_multi_light.frag"
    );

    Shader colorShader(
        "renderer/shader/mat_shaders/mat.vert",
        "renderer/shader/mat_shaders/mat.frag"
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
    floorMat.ambience = 0.04f;
    floorMat.tiling = { 30.0f, 30.0f };


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
    sphereMat.ambience = 0.06f;


    //light mat
    Material lightMat;
    lightMat.shader = &colorShader;


    //floor
    Model floor("floor", 0);

    floor.mesh = &floorMesh;
    floor.mat = &floorMat;

    floor.transform.position = {
        0.0f,
        -1.0f,
        0.0f
    };

    floor.transform.scale = {
        20.0f,
        1.0f,
        20.0f
    };


    //center sphere
    Model centerSphere("center sphere", 1);

    centerSphere.mesh = &sphereMesh;
    centerSphere.mat = &sphereMat;

    centerSphere.transform.position = {
        0.0f,
        0.0f,
        0.0f
    };

    centerSphere.transform.scale = {
        1.5f,
        1.5f,
        1.5f
    };


    //left sphere
    Model leftSphere("left sphere", 2);

    leftSphere.mesh = &sphereMesh;
    leftSphere.mat = &sphereMat;

    leftSphere.transform.position = {
        -2.5f,
        -0.25f,
        -1.0f
    };


    //right sphere
    Model rightSphere("right sphere", 3);

    rightSphere.mesh = &sphereMesh;
    rightSphere.mat = &sphereMat;

    rightSphere.transform.position = {
        2.7f,
        -0.25f,
        -0.5f
    };

    rightSphere.transform.scale = {
        0.8f,
        0.8f,
        0.8f
    };


    //left pyramid
    Model leftPyramid("left pyramid", 4);

    leftPyramid.mesh = &pyramidMesh;
    leftPyramid.mat = &pyramidMat;

    leftPyramid.transform.position = {
        -1.8f,
        -0.4f,
        2.0f
    };


    //right pyramid
    Model rightPyramid("right pyramid", 5);

    rightPyramid.mesh = &pyramidMesh;
    rightPyramid.mat = &pyramidMat;

    rightPyramid.transform.position = {
        2.0f,
        -0.4f,
        2.2f
    };

    rightPyramid.transform.scale = {
        1.4f,
        1.4f,
        1.4f
    };


    //back pyramid
    Model backPyramid("back pyramid", 6);

    backPyramid.mesh = &pyramidMesh;
    backPyramid.mat = &pyramidMat;

    backPyramid.transform.position = {
        0.0f,
        -0.4f,
        -3.0f
    };

    backPyramid.transform.scale = {
        0.8f,
        1.8f,
        0.8f
    };


    //small sphere
    Model smallSphere("small sphere", 7);

    smallSphere.mesh = &sphereMesh;
    smallSphere.mat = &sphereMat;

    smallSphere.transform.scale = {
        0.45f,
        0.45f,
        0.45f
    };


    //warm point light
    Light warmPoint(
        1.8f,
        1.0f,
        0.45f,
        0.15f,
        POINT
    );

    warmPoint.transform.position = {
        3.0f,
        2.0f,
        0.0f
    };


    //blue point light
    Light bluePoint(
        1.5f,
        0.1f,
        0.3f,
        1.0f,
        POINT
    );

    bluePoint.transform.position = {
        -3.0f,
        1.5f,
        0.0f
    };


    //green point light
    Light greenPoint(
        1.1f,
        0.1f,
        1.0f,
        0.35f,
        POINT
    );

    greenPoint.transform.position = {
        0.0f,
        1.0f,
        -4.0f
    };


    //spot light
    Light spotLight(
        2.4f,
        1.0f,
        0.9f,
        0.65f,
        SPOT
    );

    spotLight.transform.position = {
        0.0f,
        4.5f,
        0.0f
    };

    //rotation is acting as dir for now
    spotLight.transform.rotation = {
        0.0f,
        -1.0f,
        0.0f
    };


    //directional light
    Light directionalLight(
        0.20f,
        0.45f,
        0.55f,
        0.8f,
        DIRECTIONAL
    );

    directionalLight.transform.rotation = {
        -0.5f,
        -1.0f,
        -0.25f
    };


    //light objs
    Model warmLightObj("warm light obj", 10);

    warmLightObj.mesh = &sphereMesh;
    warmLightObj.mat = &lightMat;

    warmLightObj.transform.scale = {
        0.13f,
        0.13f,
        0.13f
    };


    Model blueLightObj("blue light obj", 11);

    blueLightObj.mesh = &sphereMesh;
    blueLightObj.mat = &lightMat;

    blueLightObj.transform.scale = {
        0.13f,
        0.13f,
        0.13f
    };


    Model greenLightObj("green light obj", 12);

    greenLightObj.mesh = &sphereMesh;
    greenLightObj.mat = &lightMat;

    greenLightObj.transform.scale = {
        0.13f,
        0.13f,
        0.13f
    };


    Model spotLightObj("spot light obj", 13);

    spotLightObj.mesh = &sphereMesh;
    spotLightObj.mat = &lightMat;

    spotLightObj.transform.scale = {
        0.16f,
        0.16f,
        0.16f
    };


    //scene
    Scene scene;

    scene.current_cam = &cam;


    //lights
    scene.lights.push_back(&warmPoint);
    scene.lights.push_back(&bluePoint);
    scene.lights.push_back(&greenPoint);
    scene.lights.push_back(&spotLight);
    scene.lights.push_back(&directionalLight);


    //models
    scene.models.push_back(&floor);

    scene.models.push_back(&centerSphere);
    scene.models.push_back(&leftSphere);
    scene.models.push_back(&rightSphere);
    scene.models.push_back(&smallSphere);

    scene.models.push_back(&leftPyramid);
    scene.models.push_back(&rightPyramid);
    scene.models.push_back(&backPyramid);

    //same resources beside each other
    scene.models.push_back(&warmLightObj);
    scene.models.push_back(&blueLightObj);
    scene.models.push_back(&greenLightObj);
    scene.models.push_back(&spotLightObj);


    //renderer
    Renderer renderer;

    renderer.current_cam = &cam;
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


        //move warm light around scene
        warmPoint.transform.position = {
            cos(t * 0.75f) * 3.5f,
            1.8f + sin(t * 1.4f) * 0.5f,
            sin(t * 0.75f) * 3.5f
        };


        //blue light goes around the other way
        bluePoint.transform.position = {
            cos(-t * 0.55f) * 4.0f,
            1.2f + sin(t * 0.7f) * 0.3f,
            sin(-t * 0.55f) * 4.0f
        };


        //green light moves around the back
        greenPoint.transform.position = {
            sin(t * 0.8f) * 2.0f,
            0.8f + sin(t * 1.7f) * 1.0f,
            -3.5f + cos(t * 0.5f)
        };


        //spot light moves over everything
        spotLight.transform.position = {
            sin(t * 0.45f) * 2.5f,
            4.5f,
            cos(t * 0.30f) * 1.5f
        };


        //make spot always look around center
        spotLight.transform.rotation =
            glm::normalize(
                glm::vec3(
                    sin(t * 0.35f) * 1.5f,
                    0.0f,
                    cos(t * 0.35f) * 1.5f
                )
                -
                spotLight.transform.position
            );


        //make the little light objs follow the lights
        warmLightObj.transform.position =
            warmPoint.transform.position;

        blueLightObj.transform.position =
            bluePoint.transform.position;

        greenLightObj.transform.position =
            greenPoint.transform.position;

        spotLightObj.transform.position =
            spotLight.transform.position;


        //float center sphere
        centerSphere.transform.position.y =
            0.15f +
            sin(t * 1.3f) * 0.35f;


        //left sphere circles center
        leftSphere.transform.position = {
            cos(t * 0.65f) * 2.6f,
            -0.25f,
            sin(t * 0.65f) * 2.6f
        };


        //right sphere circles opposite way
        rightSphere.transform.position = {
            cos(-t * 0.45f) * 3.2f,
            -0.25f + sin(t * 1.2f) * 0.2f,
            sin(-t * 0.45f) * 3.2f
        };


        //small sphere goes around the floating center sphere
        smallSphere.transform.position = {
            centerSphere.transform.position.x +
                cos(t * 1.8f) * 1.3f,

            centerSphere.transform.position.y +
                sin(t * 1.4f) * 0.6f,

            centerSphere.transform.position.z +
                sin(t * 1.8f) * 1.3f
        };



       

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