#include "vectors.h"

namespace visual{
    void Vectors::Draw() {
        ImGui::Begin("Hello Vectors");

        if(ImGui::CollapsingHeader("Vector Basics")){
            static float v_x, v_y;

            ImGui::SliderFloat("Vector X", &v_x, 0, 30);
            ImGui::SliderFloat("Vector Y", &v_y, 0, 30);

            m_drawList = ImGui::GetWindowDrawList();

            const ImVec2 p = ImGui::GetCursorScreenPos();

            m_drawList->AddLine(p, ImVec2{p.x + v_x * 10, p.y + v_y * 10}, ImColor{1.0f, 1.0f, 1.0f, 1.0f});
        }

        ImGui::End();
    }
}