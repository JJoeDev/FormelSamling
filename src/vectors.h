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

        void DrawVector(const ImVec2& v_a, const ImVec2& v_b, const ImColor& color);
        void DrawCanvas();
    };
}

#endif