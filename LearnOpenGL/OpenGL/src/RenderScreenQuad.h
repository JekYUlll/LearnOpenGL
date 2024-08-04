#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// �������ݣ�x, y, u, v
float quadVertices[] = {
    // λ��          // ��������
    -1.0f,  1.0f,   0.0f, 1.0f, // ���Ͻ�
    -1.0f, -1.0f,   0.0f, 0.0f, // ���½�
     1.0f, -1.0f,   1.0f, 0.0f, // ���½�
     1.0f,  1.0f,   1.0f, 1.0f  // ���Ͻ�
};

unsigned int quadVAO, quadVBO;

void RenderScreenQuadSetUp()
{
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);

}

void RenderScreenQuad()
{
    // ������Ļ�ı���
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}



