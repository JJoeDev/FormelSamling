#include "application.h"
#include "styling.h"

#include <iostream>
#include <filesystem>

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

bool App::Init(const char* title){
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

    GLFWmonitor* mon = glfwGetPrimaryMonitor();
    const GLFWvidmode* vMode = glfwGetVideoMode(mon);
    int width = vMode->width;
    int height = vMode->height;    

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if(!m_window){
        std::cerr << "GLFW WINDOW CREATION FAILED!\n";
        return false;
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable VSync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ApplyStyles();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    m_guiFlags |= ImGuiWindowFlags_NoResize;
    m_guiFlags |= ImGuiWindowFlags_NoMove;
    m_guiFlags |= ImGuiWindowFlags_NoCollapse;
    m_guiFlags |= ImGuiWindowFlags_NoDocking;
    m_guiFlags |= ImGuiWindowFlags_MenuBar;
    //m_guiFlags |= ImGuiWindowFlags_Popup;

    if(std::filesystem::exists("fonts/NotoSansMath-Regular.ttf") && std::filesystem::is_regular_file("fonts/NotoSansMath-Regular.ttf")){
        ImVector<ImWchar> ranges;
        ImFontGlyphRangesBuilder builder;
        builder.AddRanges(io->Fonts->GetGlyphRangesDefault());
        builder.AddText(u8"∀αβγδεζηθικλμνξοπρστυφχψωΓΔΘΛΞΟΠΣΦΨΩ∑∏∫√±×÷=≠≈≡∝∞∉∈∪∩⊆⊂∧∨¬⇒⇔⊢∠°′″+-×÷^∛≈≅≡=≠<>≤≥|!%∴∵∎πei→←↑↓↔↕⇆⇈⇊⇒⇔");
        builder.BuildRanges(&ranges);
        io->Fonts->AddFontFromFileTTF("fonts/NotoSansMath-Regular.ttf", 21.0f, NULL, ranges.Data);
        io->Fonts->Build();
        m_fontLoaded = true;
    }

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

    m_fontLoaded ? ImGui::Text("Current font: %s", io->Fonts[0].ConfigData.Data->Name) : ImGui::TextColored(ImColor(255, 187, 2), "[WARNING] NotoSansMath font could not be loaded");

    ImGui::Text("∀ α β γ δ ε ζ η θ ι κ λ μ ν ξ ο π ρ σ τ υ φ χ ψ ω Γ Δ Θ Λ Ξ Ο Π Σ Φ Ψ Ω ∑ ∏ ∫ √ ± × ÷ = ≠ < > ≈ ≡ ∝ ∞ ∉ ∈ ∪ ∩ ⊆ ⊂ ∧ ∨ ¬ ⇒ ⇔ ⊢ ∠ ° ′ ″ + - × ÷ ^ ∛ ≈ ≅ ≡ = ≠ < > ≤ ≥ | ! % ∴ ∵ ∎ π e i");
    ImGui::SameLine();
    ImGui::Text(" → ← ↑ ↓ ↔ ↕ ⇆ ⇈ ⇊ ⇒ ⇔");
    ImGui::Text("√(ax^2 + ay^2)");

    if(ImGui::BeginMenuBar()){
        if(ImGui::BeginMenu("Settings")){
            ImGui::MenuItem("Demo Window", nullptr, &m_showDemo);

            ImGui::SeparatorText("Application spicific");
            ImGui::MenuItem("Help", nullptr, &m_helpWindow);

            if(ImGui::MenuItem("Resizable", nullptr, &m_resizable)){
                glfwSetWindowAttrib(m_window, GLFW_RESIZABLE, m_resizable ? GLFW_TRUE : GLFW_FALSE);
            }
            
            if(ImGui::MenuItem("Quit")){
                glfwSetWindowShouldClose(m_window, GLFW_TRUE);
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    if(m_showDemo)
        ImGui::ShowDemoWindow();

    if(m_helpWindow){
        ImGui::OpenPopup("Help");

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2{0.5f, 0.5f});

        if(ImGui::BeginPopupModal("Help", nullptr, ImGuiWindowFlags_AlwaysAutoResize)){
            ImGui::Text("A help page to help you use the Foss Interactive Formelsamling");

            if(ImGui::Button("Close", ImVec2(120, 0))) {
                m_helpWindow = false;
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }

    ImGui::SetWindowPos(ImVec2{0, 0});
    ImGui::SetWindowSize(ImVec2{static_cast<float>(m_displayW), static_cast<float>(m_displayH)});

    ImGui::SetNextWindowSize(ImVec2{500, 500}, ImGuiCond_FirstUseEver);

    ImGui::Checkbox("Vectors", &m_vectorsOpen);
    if(m_vectorsOpen)
        vecs.Draw();

    ImGui::End();
    // End the main window where all gui is inside of
}
