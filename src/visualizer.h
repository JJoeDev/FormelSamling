#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <memory>

#include "../vendor/imgui/imgui.h"

namespace visual{
    class Visualizer{
    public:
        Visualizer() = default;
        Visualizer(const Visualizer&) = delete;
        void operator=(const Visualizer&) = delete;

        virtual void Draw() = 0;
    
    protected:
        ImDrawList* m_drawList;
    };
}

#endif