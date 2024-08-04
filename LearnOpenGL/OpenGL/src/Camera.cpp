#include "Camera.h"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 3.0f;
const float SENSITIVTY = 0.25f;
const float ZOOM = 45.0f;

float cameraMove = 0.0f;
float cameraSpeed = 0.0f;
const float cameraSpeed_std = 3.0f;
const float cameraSpeed_rush = cameraSpeed_std * 2.0f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 4.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

float pitch = 0.0f;
float yaw = 0.0f;
float roll = 0.0f;

float fov_y = 45.0f;
float sensitivity = 0.15f;

Camera::Camera(const glm::vec3& position, const glm::vec3& lookAt, const glm::vec3& up)
    : _position(position), _up(up), _front(glm::normalize(lookAt - position)), _right(glm::vec3(0.0f))
{
    _right = glm::normalize(glm::cross(_front, _up));
    // 根据 _front 和 _up 向量计算旋转四元数
    glm::vec3 defaultFront(0.0f, 0.0f, -1.0f); // 默认相机方向
    glm::vec3 axis = glm::cross(defaultFront, _front);
    float angle = acos(glm::dot(defaultFront, _front));
    _rotation = glm::angleAxis(angle, glm::normalize(axis));
    // 更新相机向量
    UpdateCameraVectors();
}

void Camera::Update(float deltaTime)
{
    UpdateCameraVectors();
}

void Camera::SetPosition(const glm::vec3& position)
{
    _position = position;
}

void Camera::SetRotation(const glm::quat& rotation)
{
    _rotation = rotation;
}

void Camera::Rotate(const glm::vec3& eulerAngles)
{
    glm::quat quaternion = glm::quat(glm::radians(eulerAngles));
    _rotation = quaternion * _rotation; // 先乘以新的旋转
    _rotation = glm::normalize(_rotation);
}

void Camera::Rotate(const glm::quat& rotation)
{
    _rotation = rotation * _rotation;
    _rotation = glm::normalize(_rotation);
}

void Camera::Translate(const glm::vec3& translation)
{
    _position += translation;
}

glm::mat4 Camera::GetViewMatrix() const
{
    glm::vec3 front = _rotation * glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = _rotation * _up;
    return glm::lookAt(_position, _position + front, up);
}

void Camera::UpdateCameraVectors()
{
    // 通过四元数计算前向量
    glm::vec3 front = _rotation * glm::vec3(0.0f, 0.0f, -1.0f);
    front = glm::normalize(front);
    // 计算右向量 (基于当前的上向量)
    glm::vec3 right = glm::normalize(glm::cross(front, _up));
    // 重新计算真正的上向量
    glm::vec3 up = glm::normalize(glm::cross(right, front));
    // 更新摄像机的向量
    _front = front;
    _right = right;
    _up = up;
}
