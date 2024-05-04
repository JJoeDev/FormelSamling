#include "vectors.h"

#include <cmath>

namespace visual{
    void Vectors::Draw() {
        ImGui::Begin("Hello Vectors", nullptr, ImGuiWindowFlags_NoCollapse);

        const char* vecMath[] = {"Vector Basics", "Vector + Vector"};
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
            const float sliderLimit = 20.0f;
            static float v_x, v_y, v_len;

            ImGui::Text("Vector a = (%.3f, %.3f)", v_x, v_y);
            ImGui::Text("|a| = √(ax^2 + ay^2) = %.3f", v_len);

            ImGui::Spacing();
            ImGui::SeparatorText("Interactives");
            ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.48f);
            ImGui::SliderFloat("ax", &v_x, -sliderLimit, sliderLimit); ImGui::SameLine();
            ImGui::SliderFloat("ay", &v_y, -sliderLimit, sliderLimit);
            ImGui::PopItemWidth();

            v_len = std::sqrt(v_x * v_x + v_y * v_y);
            
            DrawCanvas();

            //! Grid code is commented below
            // ImVec2 gridSpacing = ImVec2{50.0f, 50.0f};
            // for(float x = fmodf(m_canvasPos.x, gridSpacing.x); x < m_canvasSize.x; x += gridSpacing.x){
            //     m_drawList->AddLine(ImVec2{m_canvasPos.x + x, m_canvasPos.y}, ImVec2{m_canvasPos.x + x, m_canvasPos.y + m_canvasSize.y}, IM_COL32(50, 50, 50, 255));
            // }

            // for(float y = fmodf(m_canvasPos.y, gridSpacing.y); y < m_canvasSize.y; y += gridSpacing.y){
            //     m_drawList->AddLine(ImVec2{m_canvasPos.x, m_canvasPos.y + y}, ImVec2{m_canvasPos.x + m_canvasSize.x, m_canvasPos.y + y}, IM_COL32(50, 50, 50, 255));
            // }

            ImVec2 Center = ImVec2(m_canvasPos.x + m_canvasSize.x / 2, m_canvasPos.y + m_canvasSize.y / 2);            
            ImVec2 vecEnd = ImVec2{Center.x + v_x * 10, Center.y + v_y * 10};
            DrawVector(Center, vecEnd, ImColor(255, 255, 255));
            break;
        }
        case 1:{
            const float sliderLimit = 20.0f;
            static float v_x, v_y, v_x2, v_y2;
            static bool add = true;

            ImGui::SeparatorText("Example");
            ImGui::Text("Vector a = (3, 7)");
            ImGui::Text("Vector b = (6, 2)");
            ImGui::Text("Vector c = a + b == (ax + bx over ay + by)");
            ImGui::Text("Vector c = (3 + 6 over 7 + 2) = (9, 9)");

            ImGui::SeparatorText("Practical example");

            ImGui::TextColored(ImColor(0, 255, 0, 255), "Vector a = (%.3f, %.3f)", v_x, v_y);
            ImGui::TextColored(ImColor(0, 0, 255, 255), "Vector b = (%.3f, %.3f)", v_x2, v_y2);
            ImGui::TextColored(ImColor(255, 0, 0, 255), "Vector c = (%.3f, %.3f)", v_x + v_x2, v_y + v_y2);

            ImGui::Checkbox("Vector addition", &add);

            ImGui::Spacing();
            ImGui::SeparatorText("Interactives");
            ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.48f);
            ImGui::SliderFloat("ax", &v_x, -sliderLimit, sliderLimit); ImGui::SameLine();
            ImGui::SliderFloat("ay", &v_y, -sliderLimit, sliderLimit);
            ImGui::PopItemWidth();

            ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.48f);
            ImGui::SliderFloat("ax2", &v_x2, -sliderLimit, sliderLimit); ImGui::SameLine();
            ImGui::SliderFloat("ay2", &v_y2, -sliderLimit, sliderLimit);
            ImGui::PopItemWidth();

            DrawCanvas();

            ImVec2 Center = ImVec2(m_canvasPos.x + m_canvasSize.x / 2, m_canvasPos.y + m_canvasSize.y / 2);

            ImVec2 v1End = ImVec2(Center.x + v_x * 10, Center.y + v_y * 10);
            ImVec2 v2End = ImVec2(v1End.x + v_x2 * 10, v1End.y + v_y2 * 10);

            DrawVector(Center, v1End, ImColor{0, 255, 0});
            DrawVector(v1End, v2End, ImColor(0, 0, 255));
            DrawVector(Center, v2End, ImColor(255, 0, 0));
        }
        }

        ImGui::End();
    }

    // PRIVATE FUNCTIONS

    void Vectors::DrawVector(const ImVec2& v_a, const ImVec2& v_b, const ImColor& color){
        const float arrowHead = 10.0f;

        m_drawList->AddLine(v_a, v_b, color);

        // Arrow head point
        ImVec2 dir;
        dir.x = v_b.x - v_a.x;
        dir.y = v_b.y - v_a.y;

        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        if(len > 0.0f){
            dir.x /= len;
            dir.y /= len;

            // Basically just rotates the vector på 90 degrees so we can get a flat head on the main line
            ImVec2 ortho(-dir.y, dir.x);
            
            ImVec2 p1;
            ImVec2 p2;

            // Arrow head points
            p1.x = v_b.x - dir.x * arrowHead + ortho.x * (arrowHead / 2.0f);
            p1.y = v_b.y - dir.y * arrowHead + ortho.y * (arrowHead / 2.0f);

            p2.x = v_b.x - dir.x * arrowHead - ortho.x * (arrowHead / 2.0f);
            p2.y = v_b.y - dir.y * arrowHead - ortho.y * (arrowHead / 2.0f);

            m_drawList->AddTriangleFilled(v_b, p1, p2, color);
        }
    }

    void Vectors::DrawCanvas(){
        m_canvasPos = ImGui::GetCursorScreenPos();
        m_canvasSize = ImGui::GetContentRegionAvail();

        ImGui::InvisibleButton("canvas", m_canvasSize);

        m_drawList = ImGui::GetWindowDrawList();
        m_drawList->AddRectFilled(m_canvasPos, ImVec2(m_canvasPos.x + m_canvasSize.x, m_canvasPos.y + m_canvasSize.y), IM_COL32(25, 25, 25, 255));
    }
}