#include "vectors.h"

namespace visual{
    void Vectors::Render(){
        m_drawList = ImGui::GetWindowDrawList();

        ImGui::Text("Vector a = (%.3f, %.3f)", m_x, m_y);
        ImGui::SliderFloat("Vector X", &m_x, 0, 10);
        ImGui::SliderFloat("Vector Y", &m_y, 0, 10);

        const ImVec2 p = ImGui::GetCursorScreenPos();

        m_drawList->AddLine(ImVec2{p.x, p.y}, ImVec2{p.x + m_x * 10, p.y + m_y * 10}, ImColor{1.0f, 1.0f, 1.0f, 1.0f}, 2.0f);
    }
}