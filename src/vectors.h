#ifndef VECTORS_H
#define VECTORS_H

#include "visualizer.h"

namespace visual{
    class Vectors : public Visualizer{
    public:
        void Draw() override;
    
    private:
        ImVec2 m_canvasSize;
        ImVec2 m_canvasPos;
        ImVec2 m_canvasCenter;

        const float m_sliderLimit = 20.0f;

        float vec[2];
        float vec2[2];


        static void HelpMark(const char* msg);

        void BasicVector();
        void BasicVecMath();

        void DrawVector(const ImVec2& v_a, const ImVec2& v_b, const ImColor& color);
        void DrawCanvas();
    };
}

#endif