#include "application.h"

#include <iostream>

App::App(){
    glfwSetErrorCallback(glfw_error_callback);
    std::cout << "Application created!\n";
}

App::~App(){
    glfwDestroyWindow(m_window);
    glfwTerminate();

    std::cout << "Application deleted!\n";
}

void App::glfw_error_callback(int error, const char* msg){
    std::cerr << "[ GLFW ERROR ] Code: " << error << " | " << msg << std::endl;
}

bool App::Init(int width, int height, const char* title){
    // glfwSetErrorCallback(glfw_error_callback);
    if(!glfwInit()){
        std::cerr << "GLFW INIT ERROR!\n";
        return false;
    }

#if defined(__APPLE__)
    const char* glsl_version = "#version 150"
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Might remove later
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if(!m_window){
        std::cerr << "GLFW WINDOW CREATION FAILED!\n";
        return false;
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable VSync

    m_gui = new MasterGui(m_window, glsl_version);

    return true;
}

void App::Run(){
    int displayW, displayH;

    while(!glfwWindowShouldClose(m_window)){
        glfwPollEvents();

        m_gui->Gui();

        glfwGetFramebufferSize(m_window, &displayW, &displayH);
        glViewport(0, 0, displayW, displayH);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        m_gui->Render();

        glfwSwapBuffers(m_window);
    }

    delete m_gui;
    m_gui = nullptr;
}