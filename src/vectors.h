#ifndef VECTORS_H
#define VECTORS_H

#include "../vendor/imgui/imgui.h"

namespace visual{
    class Vectors{
    public:
        Vectors() = default;

        void Render();

    private:
        ImDrawList* m_drawList = nullptr;

        float m_x, m_y;
    };
}

#endif