#include "vectors.h"

#include <cmath>

namespace visual{
    void Vectors::Draw() {
        ImGui::Begin("Hello Vectors");

        if(ImGui::CollapsingHeader("Vector Basics")){
            static float v_x, v_y, v_len;

            ImGui::Text("Vector a = (%.3f, %.3f)", v_x, v_y);
            ImGui::Text("|a| = √(ax^2 + ay^2) = %.3f", v_len);

            ImGui::Spacing();
            ImGui::SeparatorText("Interactives");
            ImGui::SliderFloat("Vector X", &v_x, 0, 30);
            ImGui::SliderFloat("Vector Y", &v_y, 0, 30);

            ImVec2 canvasPos = ImGui::GetCursorScreenPos();
            ImVec2 canvasSize = ImGui::GetContentRegionAvail();
            canvasSize.x -= 25;
            canvasSize.y -= 25;

            v_len = std::sqrt(v_x * v_x + v_y * v_y);

            ImGui::InvisibleButton("canvas", canvasSize);
            m_drawList = ImGui::GetWindowDrawList();
            m_drawList->AddRectFilled(canvasPos, ImVec2{canvasPos.x + canvasSize.x, canvasPos.y + canvasSize.y}, IM_COL32(25, 25, 25, 255));

            ImVec2 gridSpacing = ImVec2(50.0f, 50.0f);
            for(float x = fmodf(canvasPos.x, gridSpacing.x); x < canvasSize.x; x += gridSpacing.x){
                m_drawList->AddLine(ImVec2{canvasPos.x + x, canvasPos.y}, ImVec2{canvasPos.x + x, canvasPos.y + canvasSize.y}, IM_COL32(50, 50, 50, 255));
            }

            for(float y = fmodf(canvasPos.y, gridSpacing.y); y < canvasSize.y; y += gridSpacing.y){
                m_drawList->AddLine(ImVec2{canvasPos.x, canvasPos.y + y}, ImVec2{canvasPos.x + canvasSize.x, canvasPos.y + y}, IM_COL32(50, 50, 50, 255));
            }

            ImVec2 vecEnd = ImVec2(canvasPos.x + v_x * 10, canvasPos.y + v_y * 10);
            m_drawList->AddLine(canvasPos, vecEnd, IM_COL32(255, 255, 255, 255));
        }
        if(ImGui::CollapsingHeader("TEST")){}

        ImGui::End();
    }
}