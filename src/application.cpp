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
    fprintf(stderr, "GLFW Error %d: %s\n", error, msg);
}

bool App::Init(int width, int height, const char* title){
    // glfwSetErrorCallback(glfw_error_callback);
    if(!glfwInit()){
        std::cerr << "GLFW INIT ERROR!\n";
        return false;
    }

#if defined(__APPLE__)
    const char* glsl_version = "#version 150";
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.5f;

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    m_guiFlags = (ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking);

    return true;
}

void App::Run(){
    while(!glfwWindowShouldClose(m_window)){
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        Gui();

        ImGui::Render();
        glfwGetFramebufferSize(m_window, &m_displayW, &m_displayH);
        glViewport(0, 0, m_displayW, m_displayH);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_window);
    }
}

void App::Gui(){
    // Begin the main window where all gui will be
    ImGui::Begin("Base Window", nullptr, m_guiFlags);

    ImGui::SetWindowPos(ImVec2{0, 0});
    ImGui::SetWindowSize(ImVec2{static_cast<float>(m_displayW), static_cast<float>(m_displayH)});

    ImGui::TextColored(ImVec4{1.0f, 0.0f, 0.0f, 1.0f}, "Sample Color Text");
    ImGui::Text("Sample Normal Text");

    if(ImGui::CollapsingHeader("Test")){
        ImGui::Text("Collapsed text");
    }

    ImGui::End();
    // End the main window where all gui is inside of
}