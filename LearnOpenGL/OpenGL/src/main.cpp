#include "pch.h"

const unsigned int WIDTH = 1792, HEIGHT = 934;
static const float aspectRatio = static_cast<float>(WIDTH) / static_cast<float>(HEIGHT); // 屏幕比例
static float image_scale[3] = { 1.0f, 1.0f, 1.0f }; // 图像缩放倍率
static float ui_scale = 1.2f; // ImGui 缩放
static ImVec4 clear_color = ImVec4(IMGUI_SKY_BLUE, 1.00f);

const char* glsl_version = "#version 330";

int main(int argc, char const* argv[])
{
    cameraSpeed = cameraSpeed_std;

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    auto window = init::Init("--- LearnOpenGL", WIDTH, HEIGHT, VERSION_1, VERSION_2, USE_CORE);
    if (!window) {
        std::cerr << "Failed to init window!" << std::endl;
        return -1;
    }

    {
        std::shared_ptr<Shader> shader = std::make_shared<Shader>("res/shaders/backpack/object.shader");
        Model Model_backpack("res/models/backpack/backpack.obj");

        shader->Use();

        GLCall(glEnable(GL_DEPTH_TEST)); // 启用深度测试
        GLCall(glEnable(GL_BLEND)); // 启用混合
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Gui::getInstance().Init(window, true, glsl_version);
        Gui::getInstance().SetFont("res/font/consola.ttf", ui_scale);
        Gui::getInstance().SetFontGlobalScale(ui_scale);

        shader->UnUse();

        while (!glfwWindowShouldClose(window)) // =====================================================>
        {
            timer::SyncTime();
            cameraMove = cameraSpeed * timer::deltaTime;
            ctrl::MoveCamera();

            Renderer::getInstance().Clear();
            Renderer::getInstance().SetBgColor(clear_color);

            shader->Use();

            glm::mat4 projection = glm::perspective(fov_y, aspectRatio, 0.1f, 100.0f);
            glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            glm::mat4 model = UNIT_MAT4;
            model = glm::translate(model, glm::vec3(0.0f));
            model = glm::scale(model, glm::vec3(image_scale[0], image_scale[1], image_scale[2]));
            shader->SetUniform<glm::mat4>("projection", projection);
            shader->SetUniform<glm::mat4>("view", view);
            shader->SetUniform<glm::mat4>("model", model);

            Model_backpack.Draw(*shader);

            Gui::getInstance().StartDraw();
            {
                ImGui::Begin("Controls");
                ImGui::ColorEdit3("Clear Color", (float*)&clear_color);

                ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / Gui::getInstance().GetIO().Framerate, Gui::getInstance().GetIO().Framerate);
                ImGui::End();
            }

            Gui::getInstance().Render(window);

            GLCall(glfwSwapBuffers(window));
            GLCall(glfwPollEvents());
        }
    }
    Gui::getInstance().CleanUp();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}