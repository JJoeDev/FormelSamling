#ifndef APPLICATION_H
#define APPLICATION_H

#include "masterGui.h"

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

    MasterGui* m_gui;

    static void glfw_error_callback(int error, const char* msg);

    GLFWwindow* m_window;
};

#endif