#ifndef APPLICATION_H
#define APPLICATION_H

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/backends/imgui_impl_glfw.h"
#include "../vendor/imgui/backends/imgui_impl_opengl3.h"

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

// App is a singleton. There can only be one
class App{
public:
    static App& GetInstance(){
        static App instance;
        return instance;
    }

    bool Init(int width, int height, const char* title);

    void Run();

private:
    App();
    ~App();

    App(const App&) = delete;
    App& operator=(const App&) = delete;

    static void glfw_error_callback(int error, const char* msg);

    void Gui();

    GLFWwindow* m_window;

    int m_displayW, m_displayH;
    ImGuiWindowFlags m_guiFlags;
};

#endif