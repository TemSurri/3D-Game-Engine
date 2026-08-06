#include "core/window_manager.h"
#include "renderer/shader/shader.h"
#include "renderer/components/model/model.h"
#include "renderer/camera/camera.h"
#include "renderer/renderer.h"
#include "renderer/components/light/light.h"
#include <stb_image.h>

int main()
{
    WindowManager windowManager;

    GLFWwindow* window = windowManager.getWindow();

    if (window == nullptr)
    {
        return -1;
    }

    // =====================================
    // PYRAMID MESH
    // =====================================

    Mesh pyramidMesh;

    glm::vec3 frontNormal{0.0f, 0.707f, 0.707f};
    glm::vec3 rightNormal{ 0.707f, 0.707f, 0.0f };
    glm::vec3 backNormal{ 0.0f, 0.707f, -0.707f };
    glm::vec3 leftNormal{ -0.707f, 0.707f, 0.0f };
    glm::vec3 bottomNormal{ 0.0f, -1.0f, 0.0f };


    // FRONT
    pyramidMesh.addVertex(Vertex{
        -0.4f, -0.4f,  0.4f,
         1.0f,  1.0f,  1.0f,
         0.0f,  0.0f, frontNormal
        });

    pyramidMesh.addVertex(Vertex{
         0.4f, -0.4f,  0.4f,
         1.0f,  1.0f,  1.0f,
         1.0f,  0.0f, frontNormal
        });

    pyramidMesh.addVertex(Vertex{
         0.0f,  0.5f,  0.0f,
         1.0f,  1.0f,  1.0f,
         0.5f,  1.0f, frontNormal
        });


    // RIGHT
    pyramidMesh.addVertex(Vertex{
         0.4f, -0.4f,  0.4f,
         1.0f,  1.0f,  1.0f,
         0.0f,  0.0f, rightNormal
        });

    pyramidMesh.addVertex(Vertex{
         0.4f, -0.4f, -0.4f,
         1.0f,  1.0f,  1.0f,
         1.0f,  0.0f, rightNormal
        });

    pyramidMesh.addVertex(Vertex{
         0.0f,  0.5f,  0.0f,
         1.0f,  1.0f,  1.0f,
         0.5f,  1.0f, rightNormal
        });


    // BACK
    pyramidMesh.addVertex(Vertex{
         0.4f, -0.4f, -0.4f,
         1.0f,  1.0f,  1.0f,
         0.0f,  0.0f, backNormal
        });

    pyramidMesh.addVertex(Vertex{
        -0.4f, -0.4f, -0.4f,
         1.0f,  1.0f,  1.0f,
         1.0f,  0.0f, backNormal
        });

    pyramidMesh.addVertex(Vertex{
         0.0f,  0.5f,  0.0f,
         1.0f,  1.0f,  1.0f,
         0.5f,  1.0f, backNormal
        });


    // LEFT
    pyramidMesh.addVertex(Vertex{
        -0.4f, -0.4f, -0.4f,
         1.0f,  1.0f,  1.0f,
         0.0f,  0.0f, leftNormal
        });

    pyramidMesh.addVertex(Vertex{
        -0.4f, -0.4f,  0.4f,
         1.0f,  1.0f,  1.0f,
         1.0f,  0.0f, leftNormal
        });

    pyramidMesh.addVertex(Vertex{
         0.0f,  0.5f,  0.0f,
         1.0f,  1.0f,  1.0f,
         0.5f,  1.0f, leftNormal
        });


    // BOTTOM
    pyramidMesh.addVertex(Vertex{
        -0.4f, -0.4f,  0.4f,
         1.0f,  1.0f,  1.0f,
         0.0f,  0.0f, bottomNormal
        });

    pyramidMesh.addVertex(Vertex{
         0.4f, -0.4f,  0.4f,
         1.0f,  1.0f,  1.0f,
         1.0f,  0.0f, bottomNormal
        });

    pyramidMesh.addVertex(Vertex{
         0.4f, -0.4f, -0.4f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, bottomNormal
        });

    pyramidMesh.addVertex(Vertex{
        -0.4f, -0.4f, -0.4f,
         1.0f,  1.0f,  1.0f,
         0.0f,  1.0f, bottomNormal
        });


    // =====================================
    // INDICES
    // =====================================

    // Four sides
    pyramidMesh.addTriangle(0, 1, 2);
    pyramidMesh.addTriangle(3, 4, 5);
    pyramidMesh.addTriangle(6, 7, 8);
    pyramidMesh.addTriangle(9, 10, 11);

    // Bottom
    pyramidMesh.addTriangle(12, 14, 13);
    pyramidMesh.addTriangle(12, 15, 14);

    pyramidMesh.initGLResources();


    // =====================================
    // PYRAMID TEXTURE
    // =====================================

    Tex meTex;

    meTex.Create(
        "resources/textures/me.jpg"
    );


 

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

            glm::vec3 Normal{ x/radius , y / radius  , z / radius };

            Vertex vertex{
                x, y, z,

                // color
                1.0f, 1.0f, 1.0f,

                // UV
                u, v, Normal
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
    mat.shininess = 1.0f;
    mat.diffuse = 3.0f;
    Shader texShader = Shader("renderer/shader/mat_shaders/mat_single_light.vert", "renderer/shader/mat_shaders/mat_single_light.frag");
    mat.shader = &texShader;
    Tex fleshTex = Tex();
    fleshTex.Create("resources/textures/flesh.jpg");
    mat.texture = &fleshTex;

    //make renderer
    Renderer renderer = Renderer();

    renderer.current_cam = &cam;
    renderer.window = &(*window);


    //putting everything together in Model
    Model cube1 = Model("meatball", 0);
    //cube1.transform.scale = { 4,0.4,4 };
    cube1.mesh = &m;
    cube1.mat = &mat;


    // =====================================
    // PYRAMID MATERIAL
    // =====================================

    Material pyramidMat;

    pyramidMat.shader = &texShader;
    pyramidMat.texture = &meTex;
    pyramidMat.diffuse = 1.0f;
    pyramidMat.shininess = 100.0f;
    pyramidMat.reflectiveness = 105.0f;

    // =====================================
    // PYRAMID MODEL
    // =====================================

    Model pyramid("Tem pyramid", 1);

    pyramid.mesh = &pyramidMesh;
    pyramid.mat = &pyramidMat;


    // Put it beside the sphere
    pyramid.transform.position.x = 1.2f;
    pyramid.transform.position.y = 0.0f;
    pyramid.transform.position.z = 0.0f;

    // Rotate it slightly so you see multiple sides
    pyramid.transform.rotation.y = 0.5f;


    //-----------------------------------
    //LIGHTING

    //dir to the light source
    Light lightSrc = Light(1.0f, 1.0f, 1.0f, 1.0f, POINT);
   
    Material lightMat;
    Shader colorShader = Shader("renderer/shader/mat_shaders/mat.vert", "renderer/shader/mat_shaders/mat.frag");

    lightMat.shader = &colorShader;
    lightMat.texture = &meTex;
    Model lightObj("light thing", 3);
    
   
    lightSrc.transform.position.x = 2.5f;
    lightSrc.transform.position.y = 2.5f;
    lightSrc.transform.scale = {0.5f, 0.5f, 0.5f};
    lightObj.transform = lightSrc.transform;
    lightObj.mat = &lightMat;
    //lightObj.mat->texture = &meTex;
    lightObj.mesh = &m;


    Tex naadTex;
    naadTex.Create("resources/textures/naadam.jpg");
    Material naadMat;
    naadMat.texture = &naadTex;
    naadMat.shader = &texShader;
    naadMat.diffuse = 0.13f;
    naadMat.shininess = 1.0f;
    naadMat.reflectiveness = 1.0f;
    
    Mesh floorMesh;



    //d
    floorMesh.addVertex(Vertex{
        -0.4f, -0.8f, -0.4f,
        1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, {0,1,0} }
        );
    //c
    floorMesh.addVertex(Vertex{
       0.4f, -0.8f, -0.4f,
       1.0f, 1.0f, 1.0f,
       0.0f, 1.0f, {0,1,0} }
       );
    //b
    floorMesh.addVertex(Vertex{
       0.4f, -0.8f, 0.4f,
       1.0f, 1.0f, 1.0f,
       1.0f, 1.0f, {0,1,0} }
       );
    //
    floorMesh.addVertex(Vertex{
       -0.4f, -0.8f, 0.4f,
       1.0f, 1.0f, 1.0f,
       1.0f, 0.0f, {0,1,0} }
       );
      

    floorMesh.addTriangle(
        0, 1, 2
    );
    floorMesh.addTriangle(
        0, 3, 2
    );

    floorMesh.initGLResources();

    Model naadFloor("naadam floor", 4);
    naadFloor.mat = &naadMat;
    naadFloor.transform.scale = { 100, 1, 100 };
    naadFloor.mesh = &floorMesh;

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

        renderer.renderModel(pyramid, lightSrc);
        renderer.renderModel(cube1, lightSrc);
        renderer.renderModel(naadFloor, lightSrc);
        renderer.renderModel(lightObj);


        float movementSpeed = 0.003f;
       
        
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        {
            lightSrc.transform.position.x += (movementSpeed);
            lightObj.transform.position.x += (movementSpeed);
        }

        if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        {
            lightSrc.transform.position.x -= (movementSpeed);
            lightObj.transform.position.x -= (movementSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        {
            lightSrc.transform.position.y += (movementSpeed);
            lightObj.transform.position.y += (movementSpeed);
        }

        if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        {
            lightSrc.transform.position.y -= (movementSpeed);
            lightObj.transform.position.y -= (movementSpeed);
        }
        

        renderer.current_cam->inputs(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    windowManager.disposeWindow(window);

    return 0;
}