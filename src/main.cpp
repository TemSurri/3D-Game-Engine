#include "core/window_manager.h"

int main()
{
    WindowManager windowManager;

    GLFWwindow* window = windowManager.getWindow();

    if (window == nullptr)
    {
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    windowManager.disposeWindow(window);

    return 0;
}