#include "camera.h"


glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(
        pos,
        pos + front,
        up
    );
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const
{
    return glm::perspective(
        glm::radians(fov),
        aspectRatio,
        nearPlane,
        farPlane
    );
}

void Camera::updateDirection()
{
    glm::vec3 direction;

    direction.x =
        std::cos(glm::radians(yaw)) *
        std::cos(glm::radians(pitch));

    direction.y =
        std::sin(glm::radians(pitch));

    direction.z =
        std::sin(glm::radians(yaw)) *
        std::cos(glm::radians(pitch));

    front = glm::normalize(direction);
}

void Camera::inputs(GLFWwindow* window)
{

    // Keyboard movement

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        pos += front * movementSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        pos -= front * movementSpeed;
    }

    glm::vec3 right = glm::normalize(glm::cross(front, up));

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        pos -= right * movementSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        pos += right * movementSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        pos += up * movementSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        pos -= up * movementSpeed;
    }

    // Mouse look

    double mouseX;
    double mouseY;

    glfwGetCursorPos(window, &mouseX, &mouseY);

    // Prevents the camera from jumping on the first frame.
    if (firstMouseInput)
    {
        previousMouseX = mouseX;
        previousMouseY = mouseY;
        firstMouseInput = false;
    }

    float offsetX =
        static_cast<float>(mouseX - previousMouseX);

    // Reversed because screen Y increases downward.
    float offsetY =
        static_cast<float>(previousMouseY - mouseY);

    previousMouseX = mouseX;
    previousMouseY = mouseY;

    offsetX *= mouseSensitivity;
    offsetY *= mouseSensitivity;

    yaw += offsetX;
    pitch += offsetY;

    pitch = glm::clamp(pitch, -89.0f, 89.0f);

    updateDirection();

    // Press Escape to release the mouse.
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstMouseInput = true;
    }

    // Click to capture it again.
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        firstMouseInput = true;
    }
}