#include "core/window_manager.h"
#include "renderer/shader/shader.h"

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

    GLuint VBO, VAO, EBO;

    //VAO creation
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


    //VBO creation
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //bind vbo
    glBindBuffer(1, VBO);

    //bind vao
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //ebo creation
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),
        indices,
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


    //unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Shader shaderColor = Shader("renderer/shader/color.vert", "renderer/shader/color.frag");


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        shaderColor.Activate();
        glBindVertexArray(VAO);
        glDrawElements(
            GL_TRIANGLES,
            3,
            GL_UNSIGNED_INT,
            nullptr
        );
        glBindVertexArray(0);




        glfwSwapBuffers(window);
        glfwPollEvents();
    }






    //clenaup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    shaderColor.Delete();






    windowManager.disposeWindow(window);

    return 0;
}