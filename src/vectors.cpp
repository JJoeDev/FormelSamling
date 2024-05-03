#include "vectors.h"

#include <cmath>

namespace visual{
    void Vectors::Draw() {
        ImGui::Begin("Hello Vectors", nullptr, ImGuiWindowFlags_NoCollapse);

        const char* vecMath[] = {"Vector Basics", "Vector +-"};
        static int vecMathIdx = 0;
        const char* vecPreviewVal = vecMath[vecMathIdx];

        if(ImGui::BeginCombo("Vectors", vecPreviewVal, ImGuiComboFlags_HeightRegular)){
            for(int i = 0; i < IM_ARRAYSIZE(vecMath); ++i){
                const bool selected = (vecMathIdx == i);
                if(ImGui::Selectable(vecMath[i], selected))
                    vecMathIdx = i;
            }

            ImGui::EndCombo();
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        switch (vecMathIdx){
        case 0:{
            static float v_x, v_y, v_len;

            ImGui::Text("Vector a = (%.3f, %.3f)", v_x, v_y);
            ImGui::Text("|a| = √(ax^2 + ay^2) = %.3f", v_len);

            ImGui::Spacing();
            ImGui::SeparatorText("Interactives");
            ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.48f);
            ImGui::SliderFloat("ax", &v_x, 0, 30); ImGui::SameLine();
            ImGui::SliderFloat("ay", &v_y, 0, 30);
            ImGui::PopItemWidth();

            v_len = std::sqrt(v_x * v_x + v_y * v_y);
            
            DrawCanvas();

            ImVec2 gridSpacing = ImVec2{50.0f, 50.0f};
            for(float x = fmodf(m_canvasPos.x, gridSpacing.x); x < m_canvasSize.x; x += gridSpacing.x){
                m_drawList->AddLine(ImVec2{m_canvasPos.x + x, m_canvasPos.y}, ImVec2{m_canvasPos.x + x, m_canvasPos.y + m_canvasSize.y}, IM_COL32(50, 50, 50, 255));
            }

            for(float y = fmodf(m_canvasPos.y, gridSpacing.y); y < m_canvasSize.y; y += gridSpacing.y){
                m_drawList->AddLine(ImVec2{m_canvasPos.x, m_canvasPos.y + y}, ImVec2{m_canvasPos.x + m_canvasSize.x, m_canvasPos.y + y}, IM_COL32(50, 50, 50, 255));
            }

            ImVec2 vecEnd = ImVec2{m_canvasPos.x + v_x * 10, m_canvasPos.y + v_y * 10};
            m_drawList->AddLine(m_canvasPos, vecEnd, IM_COL32(255, 255, 255, 255));
            break;
        }
        case 1:
            static float v_x, v_y, v_x2, v_y2;

            ImGui::TextColored(ImColor(0, 255, 0, 255), "Vector a = (%.3f, %.3f)", v_x, v_y);
            ImGui::TextColored(ImColor(0, 0, 255, 255), "Vector b = (%.3f, %.3f)", v_x2, v_y2);
            ImGui::TextColored(ImColor(255, 0, 0, 255), "Vector c = (%.3f, %.3f)", v_x + v_x2, v_y + v_y2);

            ImGui::Spacing();
            ImGui::SeparatorText("Interactives");
            ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.48f);
            ImGui::SliderFloat("ax", &v_x, 0, 30); ImGui::SameLine();
            ImGui::SliderFloat("ay", &v_y, 0, 30);
            ImGui::PopItemWidth();

            ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.48f);
            ImGui::SliderFloat("ax2", &v_x2, 0, 30); ImGui::SameLine();
            ImGui::SliderFloat("ay2", &v_y2, 0, 30);
            ImGui::PopItemWidth();

            DrawCanvas();

            // m_drawList->AddLine(ImVec2{m_canvasPos.x, m_canvasPos.y + v_y * 10}, ImVec2{m_canvasPos.x + v_x * 10, m_canvasPos.y + v_y * 10}, IM_COL32(50, 50, 50, 255));
            // m_drawList->AddLine(ImVec2{m_canvasPos.x + v_x * 10, m_canvasPos.y + v_y * 10}, ImVec2{m_canvasPos.x + v_x * 10, m_canvasPos.y}, IM_COL32(50, 50, 50, 255));

            ImVec2 v1End = ImVec2(m_canvasPos.x + v_x * 10, m_canvasPos.y + v_y * 10);
            ImVec2 v2End = ImVec2(v1End.x + v_x2 * 10, v1End.y + v_y2 * 10);
            m_drawList->AddLine(m_canvasPos, v1End, IM_COL32(0, 255, 0, 255));
            m_drawList->AddLine(v1End, v2End, IM_COL32(0, 0, 255, 255));
            m_drawList->AddLine(m_canvasPos, v2End, IM_COL32(255, 0, 0, 255));
        }

        ImGui::End();
    }

    // PRIVATE FUNCTIONS

    void Vectors::DrawCanvas(){
        m_canvasPos = ImGui::GetCursorScreenPos();
        m_canvasSize = ImGui::GetContentRegionAvail();

        ImGui::InvisibleButton("canvas", m_canvasSize);

        m_drawList = ImGui::GetWindowDrawList();
        m_drawList->AddRectFilled(m_canvasPos, ImVec2(m_canvasPos.x + m_canvasSize.x, m_canvasPos.y + m_canvasSize.y), IM_COL32(25, 25, 25, 255));
    }
}