#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// 顶点数据：x, y, u, v
float quadVertices[] = {
    // 位置          // 纹理坐标
    -1.0f,  1.0f,   0.0f, 1.0f, // 左上角
    -1.0f, -1.0f,   0.0f, 0.0f, // 左下角
     1.0f, -1.0f,   1.0f, 0.0f, // 右下角
     1.0f,  1.0f,   1.0f, 1.0f  // 右上角
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
    // 绘制屏幕四边形
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}



