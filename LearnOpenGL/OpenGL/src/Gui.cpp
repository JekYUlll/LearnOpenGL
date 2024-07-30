#include "Gui.h"

bool Gui::_initialized = false;

Gui& Gui::getInstance()
{
	static Gui instance;
	return instance;
}

void Gui::Init(GLFWwindow* window, bool install_callbacks, const char* glsl_version)
{
	if (!_initialized) {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		_io = &ImGui::GetIO();
		ImGui_ImplGlfw_InitForOpenGL(window, install_callbacks);
		ImGui_ImplOpenGL3_Init(glsl_version);
		_initialized = true;
	}
}

void Gui::SetFont(const std::string& fontPath, const float& scale)
{
	if (_io) {
		ImFontConfig font_cfg;
		font_cfg.SizePixels = scale * 13.0f;  // Example scale factor for font size
		_io->Fonts->AddFontFromFileTTF(fontPath.c_str(), font_cfg.SizePixels, &font_cfg);
		ImGui_ImplOpenGL3_CreateFontsTexture();
	}
	else {
		std::cerr << "ImGuiIO is not initialized." << std::endl;
	}
}

void Gui::SetFontGlobalScale(const float& scale)
{
	if (_io) {
		_fontScale = scale;
		_io->FontGlobalScale = _fontScale;
	}
	else {
		std::cerr << "ImGuiIO is not initialized." << std::endl;
	}
}

void Gui::StartDraw()
{
	glfwPollEvents();
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Gui::Render(GLFWwindow* window)
{
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

ImGuiIO& Gui::GetIO()
{
	if (_io) {
		return *_io;
	}
	else {
		std::cerr << "ImGuiIO is not initialized." << std::endl;
		throw std::runtime_error("ImGuiIO is not initialized.");
	}
}