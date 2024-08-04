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
extern float cameraSpeed; // �������
extern const float cameraSpeed_std; // ��׼����
extern const float cameraSpeed_rush; // ����ʱ����

extern glm::vec3 cameraPos; // ���λ��
extern glm::vec3 cameraTarget; // ���Ŀ��
extern glm::vec3 cameraDirection; // ��˵�ġ���������/Direction Vector����ָ��z��������ģ��������������ע�ӵ��Ǹ�����
extern glm::vec3 cameraFront;
extern glm::vec3 cameraRight;
extern glm::vec3 cameraUp;
extern glm::vec3 up;

extern float pitch;
extern float yaw;
extern float roll;

extern float fov_y; // �ӽǴ�С
extern float sensitivity; // ���������

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
    void Rotate(const glm::vec3& eulerAngles); // ʹ��ŷ���ǽ�����ת
    void Rotate(const glm::quat& rotation); // ֱ��ʹ����Ԫ��������ת
    void Translate(const glm::vec3& translation); // �ƶ������

    glm::mat4 GetViewMatrix() const;

    const glm::vec3& GetPosition() const { return _position; }
    const glm::quat& GetRotation() const { return _rotation; }

private:
    glm::vec3 _position;
    glm::quat _rotation; // ʹ����Ԫ����ʾ��ת
    glm::vec3 _up;
    glm::vec3 _front;
    glm::vec3 _right;

    void UpdateCameraVectors();

};

























#endif // !CAMERA_H

