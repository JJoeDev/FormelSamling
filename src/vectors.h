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

        void DrawCanvas();
    };
}

#endif