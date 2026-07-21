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