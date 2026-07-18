#include "window_manager.h"

GLFWwindow* WindowManager::getWindow() {

	
    if (!glfwInit())
    {
        std::cout << "glfw failed to init" << std::endl;
        return nullptr;
    }

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MAJOR,
        3
    );

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MINOR,
        3
    );

    glfwWindowHint(
        GLFW_OPENGL_PROFILE,
        GLFW_OPENGL_CORE_PROFILE
    );

    GLFWwindow* window = glfwCreateWindow(
        800,
        800,
        "3D Game Engine",
        nullptr,
        nullptr
    );



    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(
        reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        glfwDestroyWindow(window);
        glfwTerminate();

        std::cout << "failed to bind window" << std::endl;
        return nullptr;
        
    }


    //GLFWimage icon{};

    //int channels;

    //icon.pixels = stbi_load(
        //"resources/icons/con.png",
        //&icon.width,
        //&icon.height,
       // &channels,
        //4
    //);

    //if (icon.pixels)
    //{
       // glfwSetWindowIcon(
          //  window,
          //  1,
       //     &icon
       // );
    //
    // //   stbi_image_free(icon.pixels);
    //}

    if (window == nullptr)
    {
        std::cout << "window is null" << std::endl;
        return nullptr;
    }


    // set responsiveness

    glfwSetFramebufferSizeCallback(
        window,
        &framebufferSizeCallback
    );

    int framebufferWidth = 0;
    int framebufferHeight = 0;

    glfwGetFramebufferSize(
        window,
        &framebufferWidth,
        &framebufferHeight
    );

    framebufferSizeCallback(
        window,
        framebufferWidth,
        framebufferHeight
    );

    return window;

}

void WindowManager::disposeWindow(GLFWwindow* window) {

    if (window != nullptr)
    {
        glfwDestroyWindow(window);
    }

    glfwTerminate();


}


void WindowManager::framebufferSizeCallback(
    GLFWwindow* window,
    int width,
    int height)
{
    (void)window;

    if (width <= 0 || height <= 0)
    {
        return;
    }

    const int viewportSize =
        std::min(width, height);

    const int viewportX =
        (width - viewportSize) / 2;

    const int viewportY =
        (height - viewportSize) / 2;

    glViewport(
        viewportX,
        viewportY,
        viewportSize,
        viewportSize
    );
}