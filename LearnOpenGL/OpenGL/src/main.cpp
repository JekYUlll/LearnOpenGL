#include "pch.h"

const unsigned int WIDTH = 1792, HEIGHT = 934;
static const float aspectRatio = static_cast<float>(WIDTH) / static_cast<float>(HEIGHT); // 屏幕比例
static float image_scale[3] = { 1.0f, 1.0f, 1.0f }; // 图像缩放倍率
static float ui_scale = 1.4f; // ImGui 缩放
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
        Camera camera(cameraPos, cameraTarget, cameraUp);

        std::shared_ptr<Shader> shader = std::make_shared<Shader>("res/shaders/backpack/object.shader");
        std::shared_ptr<Shader> skybox_shader = std::make_shared<Shader>("res/shaders/skyBox.shader");
        Model Model_backpack("res/models/backpack/backpack.obj");

        Skybox skybox("res/textures/skybox");

        GLCall(glEnable(GL_DEPTH_TEST)); // 启用深度测试
        GLCall(glEnable(GL_BLEND)); // 启用混合
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Gui::getInstance().Init(window, true, glsl_version);
        Gui::getInstance().SetFont(FONT_PATH, ui_scale);

        while (!glfwWindowShouldClose(window)) // =====================================================>
        {
            timer::SyncTime();
            cameraMove = cameraSpeed * timer::deltaTime;
            ctrl::MoveCamera();

            Renderer::getInstance().Clear();
            Renderer::getInstance().SetBgColor(clear_color);

            glm::mat4 projection = glm::perspective(fov_y, aspectRatio, 0.1f, 10000.0f);
            glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            glm::mat4 model = UNIT_MAT4;
            model = glm::translate(model, glm::vec3(0.0f));
            model = glm::scale(model, glm::vec3(image_scale[0], image_scale[1], image_scale[2]));

            glm::mat4 skybox_model = UNIT_MAT4;
            skybox_model = glm::scale(skybox_model, glm::vec3(100.0f, 100.0f, 100.0f));
            glBindTexture(GL_TEXTURE_CUBE_MAP, skybox._texture->_id);

            glDepthMask(GL_FALSE);
            skybox_shader->Use();
            skybox_shader->SetUniform<glm::mat4>("projection", projection);
            skybox_shader->SetUniform<glm::mat4>("view", view);
            skybox_shader->SetUniform<glm::mat4>("model", skybox_model);
            skybox_shader->SetUniform<int>("skybox", 0);
            skybox.Draw(*skybox_shader, camera);
            skybox_shader->UnUse();
            glDepthMask(GL_TRUE);

            shader->Use();

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

/*std::cout << "⢲⣣⢟⣾⡱⣏⣞⣵⣛⣾⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣻⣵⣿⣿⣿⠿⠿⠿⠟⠛⠛⠛⠛⠛⠛⠛⠛⠻⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣯⣞⣿⣼⣷⣿⠾⣛⣛⣛⣻⣿⣿⣿⣿⣿⣿⣿⣿⡿⠷⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀         ⢉⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⡿⠿⠻⠿⠿⠿⣿⣿⢿⣿⡿⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀           ⠀⠝⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣿⣵⠟⠁⠀⠀⠀⠀                        ⠊⡛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠁⠀⠀⠀⠀⠀⠀                          ⠅⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀                           ⢃⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀                           ⡤⡀⠌⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠁                                      ⡘⡜⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠀                                    ⢀⠃⡇⢻⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀               ⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀ ⠀⠀   ⠀    ⠐⠨⠘⣏⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢐⡇⠀⠀⢰⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⡀⠀⣿⣼⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⢆⢠⠀⠰⠀⠀⠀⠇⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⢆⡎⢸⠀⣶⠀⠀⢀⠆⣤⠀⡀⠀⠀⠀⣀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣼⡆⣼⣧⣵⣴⡶⠆⠀⠀⠀⢄⠈⠛⡇⠀⢹⣿⣿⣿⣿⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠸⠂⠐⠊⠉⠉⠉⠉⢻⣿⣿⣿⣿⣿⣿⣿⣟⡀⠀⠈⠛⠈⣧⣼⡁⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡁⠀⣔⡀⠀⠀⠺⠈⣦⣿⣿⣿⣿⣿⣿⣿⣿⣷⠺⠆⠀⢠⣿⣿⠂⠀⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣦⣜⡇⣦⠀⢀⠀⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣧⣤⣤⣾⣿⣿⠁⠀ ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⠐⡂⣿⣿⣿⣿⣿⣦⣁⣤⣴⣿⣿⣿⣿⣿⣿⣿⣷⢻⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡆⠆⠼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣞⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⠿⢂⣙⡻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣻⣯⣭⣭⣽⣇⣀⠀ ⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠄⠀⠀⠀⠀⠀⠀⠀⠀⠈⣧⠀⣼⡏⣼⢟⢊⣭⣟⠿⣿⣿⣿⣿⣿⣿⣿⢟⣽⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠸⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⢰⣿⣰⡟⣰⡿⠿⠐⠈⣿⣿⣿⣿⣿⣿⠑⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠛⠙⠞⢿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣾⣵⣿⣾⣿⣿⣦⣀⡀⠹⣿⣿⣿⣿⣿⣷⡋⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢤⠟⣻⠿⠓⡽⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⢿⣿⣿⣿⣿⣿⣿⣷⣷⣦⣍⢙⠻⠿⣿⣷⢊⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢀⠈⢶⡿⠿⢿⣿⣻⣷⡹⣿⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢻⣿⣿⣿⣿⣿⣿⣿⣿⣷⢹⡖⣦⣤⡄⠘⣿⣿⣿⣿⣿⠛⡟⣿⢣⠃⠀⢸⢠⣿⡟⠛⠛⣿⣿⣼⣿⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠿⣿⣿⣿⣿⣿⣿⣿⢸⠼⣍⡧⢟⠄⠈⠙⡩⢒⠢⠭⠌⠀⠈⠀⠀⣮⢸⡇⣭⡶⣿⢿⣿⣷⢻⣿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠿⣿⣿⣿⡿⡘⢜⣣⣛⠎⢡⣞⠀⠀⠁⠈⠀⠁⠀⠀⠀⠀⢸⣦⡠⣿⢠⣍⠣⠹⣿⣯⢿⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢱⠒⢊⣹⣿⢃⡟⣦⠐⠉⢤⠸⣞⠦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣷⢐⠂⢑⣶⣾⣿⣿⣎⣿⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣶⣾⣿⣿⣿⢘⣚⠂⠈⠀⠀⠀⠭⣛⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠀⠈⠁⠻⣿⣿⣿⣿⣞⣿⣿⣿\n"
                  << "⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⣶⣶⣾⣭⣻⢿⣿⠸⠄⠀⠐⠀⠀⠀⠈⠵⢃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠌⠀⠀⠃⠘⢿⣿⣿⣿⢸⢻⣿\n"
                  << "⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠻⠿⠿⢿⣿⣿⣷⣍⠈⡰⢁⠀⠀⠠⠁⠀⡄⢿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⣶⣶⣿⣿⣿⢚⡏⠹\n"
                  << "⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⢿⣿⡗⢴⣿⣷⡸⠁⢀⠁⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢄⡻⣿⣿⢟⠅⣼⡷⠀\n"
                  << "⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠃⠂⠻⣿⣿⡆⡁⣢⢹⡿⢠⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠮⠲⣔⣫⣾⡿⠁⠀" << std::endl;*/