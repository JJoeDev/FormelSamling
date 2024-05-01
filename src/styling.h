#ifndef STYLING_H
#define STYLING_H

#include "../vendor/imgui/imgui.h"

inline void ApplyStyles(){
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.5f;
    style.WindowTitleAlign = ImVec2{0.5f, 0.5f};
}

#endif