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
        case 0:
            BasicVector();
            break;
        case 1:
            BasicVecMath();
            break;
        }

        ImGui::End();
    }

    // PRIVATE FUNCTIONS

    void Vectors::BasicVector(){
        static float vLen;

        ImGui::Text("Vector a = (%.3f, %.3f)", vec[0], vec[1]);
        ImGui::Text("|a| = √(ax^2 + ay^2) = %.3f", vLen);

        ImGui::Spacing();
        ImGui::SeparatorText("Interactives");
        ImGui::SliderFloat2("X, Y", vec, -m_sliderLimit, m_sliderLimit);

        vLen = std::sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
            
        DrawCanvas();
          
        ImVec2 vecEnd = ImVec2{m_canvasCenter.x + vec[0] * 10, m_canvasCenter.y + vec[1] * -10};
        DrawVector(m_canvasCenter, vecEnd, ImColor(255, 255, 255));
    }

    void Vectors::BasicVecMath(){
        ImGui::SeparatorText("Example");

        static bool vAdd = true;
        ImGui::Checkbox("Addition", &vAdd);

        ImGui::Text("Vector + Vector formel: "); ImGui::SameLine();
        if(vAdd)
            HelpMark("a(5, 2) + b(1,7) = c(5 + 1, 2 + 7) = c(6, 9)");
        else
            HelpMark("a(5, 2) - b(1,7) = c(5 - 1, 2 - 7) = c(4, 5)");

        ImGui::SeparatorText("Practical example");

        if(vAdd){
            ImGui::TextColored(ImColor(0, 255, 0, 255), "Vector a(%.3f, %.3f) +", vec[0], vec[1]); ImGui::SameLine();
            ImGui::TextColored(ImColor(0, 0, 255, 255), "Vector b(%.3f, %.3f) =", vec2[0], vec2[1]); ImGui::SameLine();
            ImGui::TextColored(ImColor(255, 0, 0, 255), "Vector c(%.3f, %.3f)", vec[0] + vec2[0], vec[1] + vec2[1]);
        }
        else{
            ImGui::TextColored(ImColor(0, 255, 0, 255), "Vector a(%.3f, %.3f) -", vec[0], vec[1]); ImGui::SameLine();
            ImGui::TextColored(ImColor(0, 0, 255, 255), "Vector b(%.3f, %.3f) =", vec2[0], vec2[1]); ImGui::SameLine();
            ImGui::TextColored(ImColor(255, 0, 0, 255), "Vector c(%.3f, %.3f)", vec[0] - vec2[0], vec[1] - vec2[1]);
        }


        ImGui::Spacing();
        ImGui::SeparatorText("Interactives");

        ImGui::SliderFloat2("a(X, Y)", vec, -m_sliderLimit, m_sliderLimit);
        ImGui::SliderFloat2("b(X, Y)", vec2, -m_sliderLimit, m_sliderLimit);

        DrawCanvas();

        ImVec2 v1End = ImVec2(m_canvasCenter.x + vec[0] * 10, m_canvasCenter.y + vec[1] * -10);

        if(vAdd){
            ImVec2 v2End = ImVec2(v1End.x + vec2[0] * 10, v1End.y + vec2[1] * -10); 
            DrawVector(m_canvasCenter, v1End, ImColor{0, 255, 0});
            DrawVector(v1End, v2End, ImColor(0, 0, 255));
            DrawVector(m_canvasCenter, v2End, ImColor(255, 0, 0));
        }
        else{
            ImVec2 v2End = ImVec2(m_canvasCenter.x + vec2[0] * 10, m_canvasCenter.y + vec2[1] * -10);
            DrawVector(m_canvasCenter, v1End, ImColor(0, 255, 0));
            DrawVector(m_canvasCenter, v2End, ImColor(0, 0, 255));
            DrawVector(v1End, v2End, ImColor(255, 0, 0));
        }
    }

    // PRIVATE HELPER FUNCTIONS

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

            // The orthographic vector. Basically a vector rotated 90 degrees from our current vector
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
        m_canvasCenter = ImVec2(m_canvasPos.x + m_canvasSize.x / 2, m_canvasPos.y + m_canvasSize.y / 2);

        const ImColor canvasGray = ImColor(45, 45, 45);

        ImGui::InvisibleButton("canvas", m_canvasSize);

        m_drawList = ImGui::GetWindowDrawList();
        m_drawList->AddRectFilled(m_canvasPos, ImVec2(m_canvasPos.x + m_canvasSize.x, m_canvasPos.y + m_canvasSize.y), ImColor(25, 25, 25, 255));

        m_drawList->AddLine(ImVec2{m_canvasPos.x, m_canvasCenter.y}, ImVec2{m_canvasPos.x + m_canvasSize.x, m_canvasCenter.y}, canvasGray);
        m_drawList->AddLine(ImVec2{m_canvasCenter.x, m_canvasPos.y}, ImVec2{m_canvasCenter.x, m_canvasPos.y + m_canvasSize.y}, canvasGray);
    }

    void Vectors::HelpMark(const char* msg){
        //ImGui::TextDisabled("(?)");
        ImGui::TextColored(ImColor(255, 229, 0), "(?)");
        if(ImGui::BeginItemTooltip()){
            ImGui::TextUnformatted(msg);
            ImGui::EndTooltip();
        }
    }
}