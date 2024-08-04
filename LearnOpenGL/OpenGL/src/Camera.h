#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Component.h"

extern float cameraMove;
extern float cameraSpeed; // 相机移速
extern const float cameraSpeed_std; // 标准移速
extern const float cameraSpeed_rush; // 加速时移速

extern glm::vec3 cameraPos; // 相机位置
extern glm::vec3 cameraTarget; // 相机目标
extern glm::vec3 cameraDirection; // 所说的「方向向量/Direction Vector」是指向z的正方向的，而不是摄像机所注视的那个方向
extern glm::vec3 cameraFront;
extern glm::vec3 cameraRight;
extern glm::vec3 cameraUp;
extern glm::vec3 up;

extern float pitch;
extern float yaw;
extern float roll;

extern float fov_y; // 视角大小
extern float sensitivity; // 鼠标灵敏度

extern const float YAW;
extern const float PITCH;
extern const float SPEED;
extern const float SENSITIVTY;
extern const float ZOOM;

class Camera : public Component
{
public:
    Camera(const glm::vec3& position, const glm::vec3& lookAt, const glm::vec3& up);

    void Update(float deltaTime) override;

    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::quat& rotation);
    void Rotate(const glm::vec3& eulerAngles); // 使用欧拉角进行旋转
    void Rotate(const glm::quat& rotation); // 直接使用四元数进行旋转
    void Translate(const glm::vec3& translation); // 移动摄像机

    glm::mat4 GetViewMatrix() const;

    const glm::vec3& GetPosition() const { return _position; }
    const glm::quat& GetRotation() const { return _rotation; }

private:
    glm::vec3 _position;
    glm::quat _rotation; // 使用四元数表示旋转
    glm::vec3 _up;
    glm::vec3 _front;
    glm::vec3 _right;

    void UpdateCameraVectors();

};

























#endif // !CAMERA_H

