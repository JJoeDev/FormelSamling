#ifndef MASTER_GUI_H
#define MASTER_GUI_H

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/backends/imgui_impl_glfw.h"
#include "../vendor/imgui/backends/imgui_impl_opengl3.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

class MasterGui{
public:
    MasterGui(GLFWwindow* window, const char* glslVersion);
    ~MasterGui();

    void Gui();
    inline void Render() { ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); }

private:
    bool m_open = true;
    ImGuiWindowFlags m_flags;
};

#endif